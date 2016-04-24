// *************************************************************************************
//	TTFTriangulator2DLinear.h
//
//		Triangulator that emits 2D glyphs without curvature data.
//		Curves are approximated by linear segments.
//		The function GetCurveDivideCount() must be overriden.
//
//																																Ryan Boghean
//																																April 2012
//																																January 2014
//																																June 2014
//																																April 2015
//
// *************************************************************************************

# pragma once

# include <exception>
# include <vector>
# include <cstdint>
# include <algorithm>

# include "TTFExceptions.h"
# include "TTFMath.h"
# include "TTFTypes.h"
# include "TTFTriangulator2D.h"


// ---------------------------------------------------------------------------------------------------------------------------
//	TTFCore namespace
// ---------------------------------------------------------------------------------------------------------------------------

namespace TTFCore {


// ---------------------------------------------------------------------------------------------------------------------------
//	Triangulator2DLinear
// ---------------------------------------------------------------------------------------------------------------------------

template <typename TVert, typename TTri> class Triangulator2DLinear : public Triangulator2D<TVert,TTri> {
	friend class Font;

	protected:
		// Triangulator2DLinear specific functions
		void AddCurvatureEdges(TVert pp, TVert ip, TVert pc);
		void TraceContourHelper(const ContourPoint& cp, TVert& pp, TVert& ip, bool& ppc);
		void TraceContour(CItr begin, CItr end);
		void TraceContour();

		// Triangulator private interface
		std::vector<ContourPoint>& GetContours();		// returns a vector to the contour vector
		void AppendTriangulation();									// triangulates and appends any contour data into the mesh data

		virtual size_t GetCurveDivideCount(TVert p0, TVert p1, TVert p2) = 0;		// returns the number of edge sub-divisions for a given curve (0 = straight line, 1 = 2 edges, 2 = 3, ect...)

	public:
		Triangulator2DLinear();
		Triangulator2DLinear(TriangulatorFlags);
	};


// ---------------------------------------------------------------------------------------------------------------------------
//	template code
// ---------------------------------------------------------------------------------------------------------------------------

// ----- constructor/destructor -----
template <typename TVert, typename TTri> Triangulator2DLinear<TVert, TTri>::Triangulator2DLinear() :
	Triangulator2D<TVert,TTri>(TriangulatorFlags::none) {
	}

template <typename TVert, typename TTri> Triangulator2DLinear<TVert, TTri>::Triangulator2DLinear(TriangulatorFlags flags_) :
	Triangulator2D<TVert,TTri>(flags_) {
	}


// ----- Triangulator2DLinear specific functions -----
template <typename TVert, typename TTri> void Triangulator2DLinear<TVert, TTri>::AddCurvatureEdges(TVert pp, TVert ip, TVert pc) {
	// assume pp has been pushed onto the vertex 'stack' and is the last vertex

	// get point count for curve
	size_t j = std::min<size_t>(GetCurveDivideCount(pp, ip, pc), 0xfffe);
	uint16_t k = static_cast<uint16_t>(0xffff) / static_cast<uint16_t>(j + 1);	

	// create edges
	uint16_t f = k;
	for (size_t i = 0; i < j; ++i, f += k) {
		TVert np = quad_lerp(pp,ip,pc,f);				// new interpolated point
		verts.push_back(np);
		size_t n = verts.size();
		edges.push_back(Edge(n - 2,n - 1));
		}
	verts.push_back(pc);
	size_t n = verts.size();
	edges.push_back(Edge(n - 2,n - 1));
	}

template <typename TVert, typename TTri> void Triangulator2DLinear<TVert, TTri>::TraceContourHelper(const ContourPoint& cp, TVert& pp, TVert& ip, bool& ppc) {

	// intialize point variables
	TVert pc = cp.pos;					// point current/under consideration
	bool cpc = cp.OnCurve();			// current point on curve

	// determine action
	if (ppc && cpc) {
		verts.push_back(pc);						// add vertex
		size_t n = verts.size();
		edges.push_back(Edge(n-2,n-1));		// add edge
		pp = pc;
		}
	else if (ppc && !cpc) {
		ip = pc;
		ppc = false;
		}
	else if (!ppc && cpc) {
		AddCurvatureEdges(pp,ip,pc);		// pp is already on the verts 'stack', ip is just a control point, pc will be added by thsis function	
		pp = pc;
		ppc = true;
		}
	else if (!ppc && !cpc) {
		TVert np = MidPoint(ip, pc);
		AddCurvatureEdges(pp,ip,np);		// pp is already on the verts 'stack', ip is just a control point, np will be added by this function	
		pp = np;
		ip = pc;
		//ppc = false;
		}
	}

template <typename TVert, typename TTri> void Triangulator2DLinear<TVert, TTri>::TraceContour(CItr begin, CItr end) {

	// sanity checks
	if ( (end - begin) == 0 ) return;
	if ( (end - begin) < 2 ) throw InvalidFontException("Cannot trace contour, contour length too small.");

	// init variables
	size_t vbo = verts.size();				// store offset of 1st vertex
	size_t ebo = edges.size();				// store offset of 1st edge

	// trace contour
	if (begin->OnCurve()) {
		TVert pp = begin->pos;					// previous point on curve
		TVert ip;										// intermediate (off curve) point/control point
		bool ppc = true;							// previous point was on the curve
		verts.push_back(pp);					// add 1st vertex to vertices of trace
	
		for (auto i = begin + 1; i != end; ++i) TraceContourHelper(*i,pp,ip,ppc);
		TraceContourHelper(*end,pp,ip,ppc);
		TraceContourHelper(*begin,pp,ip,ppc);
		}
	else if ( (begin + 1)->OnCurve() ) {
		TVert pp = (begin + 1)->pos;
		TVert ip;
		bool ppc = true;
		verts.push_back(pp);
	
		for (auto i = begin + 2; i != end; ++i) TraceContourHelper(*i,pp,ip,ppc);
		TraceContourHelper(*end,pp,ip,ppc);
		TraceContourHelper(*begin,pp,ip,ppc);
		TraceContourHelper(*(begin + 1),pp,ip,ppc);
		}
	else {	
		// neither begin nor begin + 1 is OnCurve
		// we have to create a new ContourPoint to start the contour
		ContourPoint cp;
		cp.end_point = false;
		cp.flags = 1;					// on curve
		cp.pos = MidPoint(begin->pos, (begin + 1)->pos);

		TVert pp = cp.pos;
		TVert ip;
		bool ppc = true;
		verts.push_back(pp);

		for (auto i = begin + 1; i != end; ++i) TraceContourHelper(*i,pp,ip,ppc);
		TraceContourHelper(*end,pp,ip,ppc);
		TraceContourHelper(*begin,pp,ip,ppc);
		TraceContourHelper(cp,pp,ip,ppc);
		}

	// store offset of last edge
	size_t eeo = edges.size() - 1;
	verts.pop_back();							// since there are no curves, the last vertex is never needed

	// stich last vertex to first vertex
	// only done for edges as tri's don't need their linked list
	// as well there is no guarantee for tris, while edges are guaranteed to have been added to the edge list
	edges.back().i1 = vbo;

	// create edge linked list
	edges[ebo].pe = eeo;
	edges[ebo].ne = ebo + 1;
	for (size_t i = ebo + 1; i < eeo; ++i) {
		edges[i].pe = i - 1;
		edges[i].ne = i + 1;
		}
	edges[eeo].pe = eeo - 1;
	edges[eeo].ne = ebo;
	}

template <typename TVert, typename TTri> void Triangulator2DLinear<TVert, TTri>::TraceContour() {
	
	CItr begin = contours.begin();
	CItr end = contours.end();

	if (end - begin == 0) return;
	CItr contour_begin = begin;
	for (auto i = begin + 1; i != end; ++i) {
		if (i->end_point) {
			TraceContour(contour_begin, i);
			contour_begin = i + 1;
			}
		}
	}


// ----- Triangulator private interface -----
template <typename TVert, typename TTri> std::vector<ContourPoint>& Triangulator2DLinear<TVert, TTri>::GetContours() {
	return contours;
	}

template <typename TVert, typename TTri> void Triangulator2DLinear<TVert, TTri>::AppendTriangulation() {
	// Clear() has been called,  GetContours() called and the contour points filled

	TraceContour();
	TriangulateEdges((flags & TriangulatorFlags::use_cdt) == TriangulatorFlags::use_cdt);
	CreateTris();
	if (bold_offset != 0) ApplyBold();
	if (italic_offset_x != 0 && italic_offset_y != 0) ApplyItalic();

	if ((flags & TriangulatorFlags::remove_unused_verts) == TriangulatorFlags::remove_unused_verts) {
		RemoveUnusedVerts();
		}

	// clear temporary data (if the triangulator is copied, this does not need to be copied with it)
	contours.clear();
	edges.clear();
	segs.clear();
	bounds.clear();
	tri_edges.clear();
	}


// ---------------------------------------------------------------------------------------------------------------------------
//	End
// ---------------------------------------------------------------------------------------------------------------------------

}			// end of TTFCore namespace

