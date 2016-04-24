#ifndef __CommonHeader_H__
#define __CommonHeader_H__

typedef unsigned long long ulonglong;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#include <windows.h>
#include <stdio.h>
#include <map>
#include <string.h>
#include <random>
#include <cstdlib>
#include <fstream>

#include <thread>
#include <mutex>

#define assert myassert

#include <gl/GL.h>
#include <gl/GLU.h>

#include <SDL.h>
#include <SDL_audio.h>
#include "Libraries/SDL2_mixer-2.0.1/include/SDL_mixer.h"

#define SAFE_DELETE(x) { delete x; x=0; }
#define SAFE_DELETE_ARRAY(x) { delete[] x; x=0; }

#define DRAW_TEXT true
#define LOAD_SOUND true
#define DRAW_LIGHTS true

#include "Core/Utility/Helpers.h"
#include "Core/Utility/Utility.h"
#include "Core/Math/Vector.h"
#include "Core/Math/MyMatrix.h"
typedef MyMatrix mat4;
typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Vector4 vec4;

#include "Core/Utility/InputManager.h"
#include "Core/InputEvent.h"
#include "Core/GL/GLExtensions.h"

#include "Core/Utility/Pool.h"
#include "Core/Utility/ContactListener.h"


#define math_e 2.71828

#include "Game/Mesh/VertexFormat.h"

#include "Libraries/lodepng/lodepng.h"
#include "Libraries/Box2D/Box2D/Box2D/Box2D.h"
#include "Libraries/cJSON/cJSON.h"
#include "SDL_audio.h"

#include "Core/Utility/NathanPringleHelperFunction.h"

#include "Libraries/TTF/TTF.h"

#include "Core/Utility/ShaderProgram.h"

#include "Core/FBODefinition.h"

#include "Game/Mesh/Mesh.h"
#include "Game/Mesh/AnimatedMesh.h"
#include "Game/Mesh/ParticleMesh.h"

#include "Game/Box2D/Box2DDebugDraw.h"
#include "Game/Box2D/Box2DWorld.h"

#include "Game/Base/GameObject.h"
#include "Game/Base/LightObject.h"
#include "Game/Base/ParticleEmitter.h"
#include "Game/Custom Emitters/PortalEmitter.h"
#include "Game/Base/PickUp.h"
#include "Game/PlayerObject.h"
#include "Game/EnemyObject.h"
#include "Game/CameraObject.h"
#include "Game/Base/Scene.h"
#include "Game/Base/Game.h"
#include "Game/ScoreDisplay.h"
#include "Game/Base/LightObject.h"

#include "Game/GameScene.h"
#include "Game/GameOverScene.h"
#include "Game/MainMenuScene.h"
#include "Game/PreloaderScene.h"

#include "Game/GunObjects/BarrelModifier.h"
#include "Game/GunObjects/Bullet.h"
#include "Game/GunObjects/BulletModifier.h"
#include "Game/GunObjects/Effect.h"
#include "Game/GunObjects/Gun.h"

#include "Game/GunObjects/BarrelModifiers/PistolBarrelModifier.h"
#include "Game/GunObjects/BarrelModifiers/AssaultRifleBarrelModifier.h"
#include "Game/GunObjects/BarrelModifiers/ShotgunBarrelModifier.h"
#include "Game/GunObjects/BarrelModifiers/SawedOffShotgunBarrelModifier.h"
#include "Game/GunObjects/BarrelModifiers/SMGBarrelModifier.h"
#include "Game/GunObjects/BarrelModifiers/RifleBarrelModifier.h"

#include "Game/GunObjects/BulletModifiers/SinBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/SpeedBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/AirMineBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/CircleBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/BouncyBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/FireBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/PoisonBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/FreezeBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/SuperSinusoidalBulletModifier.h"
#include "Game/GunObjects/BulletModifiers/DamageBulletModifier.h"

#include "Game/Chain/ChainLink.h"

#include "Core/Utility/Label.h"
#include "Core/Utility/AudioManager.h"
#include "Game/HUD.h"



#endif //__CommonHeader_H__
