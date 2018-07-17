/*==============================================================================
            Copyright (c) 2010-2013 QUALCOMM Austria Research Center GmbH.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
            
@file 
    MultiTargets.cpp

@brief
    Sample for MultiTargets

==============================================================================*/


#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <QCAR/QCAR.h>
#include <QCAR/CameraDevice.h>
#include <QCAR/Renderer.h>
#include <QCAR/VideoBackgroundConfig.h>
#include <QCAR/Trackable.h>
#include <QCAR/TrackableResult.h>
#include <QCAR/Tool.h>
#include <QCAR/TrackerManager.h>
#include <QCAR/ImageTracker.h>
#include <QCAR/ImageTarget.h>
#include <QCAR/MultiTarget.h>
#include <QCAR/CameraCalibration.h>
#include <QCAR/UpdateCallback.h>
#include <QCAR/DataSet.h>

#include "SampleMath.h"
#include "SampleUtils.h"
#include "Texture.h"
#include "CubeShaders.h"
#include "DividedCube.h"
#include "3D_models.h"


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct BoundingBox {
	float xmax, xmin, ymax, ymin, zmax, zmin;
} BOUNDINGBOX;

// money dropping game
typedef struct FallingBomb {
	BOUNDINGBOX bb;
	float height, pos, angle;
	bool isBomb;
	bool isActive;
} FALLINGBOMB;

FALLINGBOMB bomb[15];
unsigned int bombcount;
bool moneydown_init = false;
bool moneydown_start = false;
int pet_money_HP = 3;
int collected_money = 0;

// shoot em up game:
typedef struct Bullet {
	BOUNDINGBOX bb;
	float posX, posY;
	float speedX, speedY;
	bool isActive;
} BULLET;

typedef struct Enemy {
	BOUNDINGBOX bb;
	float posX, posY;
	float speedX, speedY;
	int hp;
	bool isAlive;
	bool isDragon;
} ENEMY;

ENEMY enemy[10];
unsigned int enemycount;
BULLET bullet[40];
unsigned int bulletcount;
bool bullet_flower_isActive = false;

int pet_shoot_HP = 3;
int score = 0;
int shootemup_hp = 100;
bool shootemup_init = false;
bool shootemup_start = false;

typedef struct Particle {
	float lifetime;
	float posX, posY;
	float speedX, speedY;
	float size;
	bool isActive;
} PARTICLE;

PARTICLE bubble[10][7];
int bubble_num = 7;

typedef struct Item {
	BOUNDINGBOX bb;
	float posX, posY;
	float speedX, speedY;
	int type;
	bool isActive;
} ITEM;
ITEM item[10];

//Beleaguered game:
typedef struct Zombie {
	BOUNDINGBOX bb;
	float posX, posY, posZ;
	float speedX, speedZ, angle;
	float hp;
	bool isAlive;
} ZOMBIE;

typedef struct Missile {
	BOUNDINGBOX bb;
	float posX, posY, posZ;
	float speedX, speedY, speedZ;
	bool isActive;
} MISSILE;

#define ZOMBIECOUNT  10
#define WAVEZOMBIES     3
ZOMBIE zombie[ZOMBIECOUNT];
MISSILE missile[10];
unsigned int missilecount;
int pet_zombie_HP = 3;

bool shotgun_init = false;
bool shotgun_enable = false;
bool shotgun_isShot = false;
bool zombie_new_wave = false;
int zombie_wave = 0;
float wave_interval = 5.0;

// GOODS PRICE
#define BERRY_PRICE     15
#define CHEESE_PRICE    10
#define BEAR_PRICE   100
#define CAT_PRICE    150
#define BULLET1_PRICE   100
#define BULLET2_PRICE   150

// Sound:
#define SHOOT_SOUND     0
#define BITE_SOUND      1
#define BOOM_SOUND      2
#define SLURP_SOUND     3
#define SMILE_SOUND     4
#define DIE_SOUND       5
#define HURT_SOUND      6
#define MISSILE_SOUND   7
#define COIN_SOUND      8
#define BOMB_SOUND   	9
#define BUYING_SOUND    10
#define NOMONEY_SOUND   11
#define USE_SOUND       12
#define ZOMBIE_SOUND    13

// Textures:
#define MESSAGE_NO_FOOD         57
#define TEXTURE_MULTIPLY_ICON   56
#define TEXTURE_MONEY_ICON      55
#define TEXTURE_BEST_SCORE      54
#define TEXTURE_BULLET_ARROW    53
#define TEXTURE_BULLET_LV3	    52
#define TEXTURE_BULLET_LV2	    51
#define TEXTURE_GAME_MESSAGE    50
#define TEXTURE_SHOP_MESSAGE    49
#define TEXTURE_HUNGRY_MESSAGE  48
#define TEXTURE_ZOMBIE          47
#define TEXTURE_TARGET          46
#define TEXTURE_LIGHTBALL       45
#define TEXTURE_MONEY           44
#define TEXTURE_DRAGON_STATE3   43
#define TEXTURE_DRAGON_STATE2   42
#define TEXTURE_DRAGON_STATE1   41
#define TEXTURE_CRYSTAL_PURPLE  40
#define TEXTURE_CRYSTAL_BLUE    39
#define TEXTURE_BP_FRAME     38
#define TEXTURE_BP_BAR       37
#define TEXTURE_BAT_STATE3   36
#define TEXTURE_BAT_STATE2   35
#define TEXTURE_DIE3         34
#define TEXTURE_DIE2         33
#define TEXTURE_DIE1         32
#define TEXTURE_SCORE        31
// 21 ~ 30 : Texture of numbers
#define TEXTURE_BUBBLE       20
#define TEXTURE_HURT3        19
#define TEXTURE_SMILE3       18
#define TEXTURE_EAT3         17
#define TEXTURE_NORMAL3      16
#define TEXTURE_HURT2        15
#define TEXTURE_SMILE2       14
#define TEXTURE_EAT2         13
#define TEXTURE_NORMAL2      12
#define TEXTURE_BULLET       11
#define TEXTURE_BAT_STATE1   10
#define TEXTURE_HEART         9
#define TEXTURE_SHOP          8
#define TEXTURE_HURT1         7
#define TEXTURE_SMILE1        6
#define TEXTURE_COIN          5
#define TEXTURE_TACHAS        4
#define TEXTURE_BERRY         3
#define TEXTURE_EAT1          2
#define TEXTURE_CHEESE        1
#define TEXTURE_NORMAL1        0

int Texture_num[10] = { 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
int Skin_equip_normal = 0;
int Skin_equip_eat    = 2;
int Skin_equip_hurt   = 7;
int Skin_equip_smile  = 6;
int Skin_equip_die    = 32;
int message_type      = 49;

int textureCount                = 0;
Texture** textures              = 0;

// OpenGL ES 2.0 specific:
unsigned int shaderProgramID    = 0;
GLint vertexHandle              = 0;
GLint normalHandle              = 0;
GLint textureCoordHandle        = 0;
GLint mvpMatrixHandle           = 0;
GLint texSampler2DHandle        = 0;

// Screen dimensions:
unsigned int screenWidth        = 0;
unsigned int screenHeight       = 0;

// Indicates whether screen is in portrait (true) or landscape (false) mode
bool isActivityInPortraitMode   = false;

// The projection matrix used for rendering virtual objects:
QCAR::Matrix44F projectionMatrix;

// Constants:
static const float kCubeScaleX    = 120.0f * 0.75f / 2.0f;
static const float kCubeScaleY    = 120.0f * 1.00f / 2.0f;
static const float kCubeScaleZ    = 120.0f * 0.50f / 2.0f;

bool modelPoseIsStatic = false;
QCAR::Matrix44F stableModelViewProjection;

bool init_status = true;
int face_change_count = 0; // Face in chatting
double prevTime_talk;
bool AdvActive = false;
bool ShopActive = false;
bool FoodActive = false;
bool food_menu = false;
bool main_menu = true;
bool call_cheese = false;
bool call_strawberry = false;
bool isTalk = false;
bool isEat = false;
bool isSmile = false;
bool isHurt = false;
bool isDie = false;
bool no_food_message = false;
bool display_message = false;

// Data needs to be saved
int total_money = 0;
int top_score = 0;
int pet_BP = 50;
int berryHolding = 3;
int cheeseHolding = 3;
bool buy_bear = false;
bool buy_cat = false;
bool buy_bullet1 = false;
bool buy_bullet2 = false;
int arm_equip_type = TEXTURE_BULLET_ARROW;
// Skin_equip_normal = 0;

void playSoundEffect(int soundIndex, float volume);

void showMainButton();
void hideMainButton();
void showFoodButton();
void hideFoodButton();

void showShopInterface();
void hideShopInterface();
void showUseCat();
void showUseRabbit();
void showUseBear();
void showSkinCat();
void showSkinRabbit();
void showSkinBear();

void showUseArrow();
void showUseBullet1();
void showUseBullet2();
void showArrow();
void showBullet1();
void showBullet2();

void enableBuyBerry();
void enableBuyCheese();
void cannotBuyBerry();
void cannotBuyCheese();

void showAdvInterface();
void hideAdvInterface();
void showShotButton();

void transmitData(int money_SaveData, int score_SaveData, int BP_SaveData, bool cat_SaveData, bool bear_SaveData,
		          int pet_Type, int berry_SaveData, int cheese_SaveData, bool bullet1_Data, bool jbullet2_Data, int arm_type);
void displayMessage(char* message);

void NumberDisplay(int count, float x_post, float y_post, QCAR::Matrix44F& ModelMatrix, QCAR::Matrix44F& ProjectionMatrix);
void CreateItem(ITEM *item, float startX, float startY);
void MoveItem(ITEM *item, float dt);
void CreateParticle(PARTICLE *particle, int num_particle, float explodeX, float explodeY);
void EvolveParticle(PARTICLE *particle, int num_particle, float dt);
void initMIT();
void loadIdentity(QCAR::Matrix44F& modelViewMatrix);
void draw2DPicture(int textureID, QCAR::Matrix44F& ProjectionMatrix);
void createBoundingBox(BOUNDINGBOX *b, float *o, int indices);
void calculateBoundingBox(BOUNDINGBOX *b, QCAR::Matrix44F& transformMatrix);
bool BoundingBoxIntersect(BOUNDINGBOX b1, BOUNDINGBOX b2);
double getCurrentTime();

JavaVM* javaVM;
jobject activityObj;
jclass activityClass;

jmethodID jmethod_playSoundEffect;
jmethodID jmethod_showFoodButton;
jmethodID jmethod_hideFoodButton;
jmethodID jmethod_showMainButton;
jmethodID jmethod_hideMainButton;
jmethodID jmethod_showAdvInterface;
jmethodID jmethod_hideAdvInterface;
// Shop Interface
jmethodID jmethod_showShopInterface;
jmethodID jmethod_hideShopInterface;
jmethodID jmethod_showUseCat;
jmethodID jmethod_showUseRabbit;
jmethodID jmethod_showUseBear;
jmethodID jmethod_showSkinCat;
jmethodID jmethod_showSkinRabbit;
jmethodID jmethod_showSkinBear;

jmethodID jmethod_showUseArrow;
jmethodID jmethod_showUseBullet1;
jmethodID jmethod_showUseBullet2;
jmethodID jmethod_showArrow;
jmethodID jmethod_showBullet1;
jmethodID jmethod_showBullet2;

jmethodID jmethod_enableBuyBerry;
jmethodID jmethod_enableBuyCheese;
jmethodID jmethod_cannotBuyBerry;
jmethodID jmethod_cannotBuyCheese;

jmethodID jmethod_showShotButton;

jmethodID jmethod_transmitData;
jmethodID jmethod_displayMessage;


QCAR::MultiTarget* mit = NULL;

QCAR::DataSet* dataSet = 0;

// Here we define a call-back that is executed every frame right after the
// Tracker finished its work. This is the ideal place to modify trackables.
// Always be sure to not try modifying something that was part of the state,
// since state objects cannot be modified. Doing this will crash your
// application.
//
struct MyUpdateCallBack : public QCAR::UpdateCallback
{
    virtual void QCAR_onUpdate(QCAR::State& state)
    {
        // Comment in the following lines to remove the bottom part of the
        // box at run-time. The first time this is executed, it will actually
        // work. After that the box has only five parts and the call will be
        // ignored (returning false).
        // 
        //if(mit!=NULL)
        //{
        //    mit->removePart(5);
        //}
    }
} myUpdateCallBack;


JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void* nReserved)
{
    // Store VM so that we can retrieve the JNI environment any time from
    // any thread
    javaVM = vm;

    return JNI_VERSION_1_4;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeFood(JNIEnv*, jobject)
{
	showFoodButton();
	hideMainButton();
	food_menu = true;
	main_menu = false;
	face_change_count = 0;
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeCheese(JNIEnv*, jobject)
{
	if(cheeseHolding > 0){
		FoodActive = !FoodActive;
		call_cheese = true;
		cheeseHolding -= 1;
	}
	else{
		showMainButton();
		main_menu = true;
		no_food_message = true;
		prevTime_talk = getCurrentTime();
	}
	food_menu = false;
	hideFoodButton();
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeBerry(JNIEnv*, jobject)
{
	if(berryHolding > 0){
		FoodActive = !FoodActive;
		call_strawberry = true;
		berryHolding -= 1;
	}
	else{
		showMainButton();
		main_menu = true;
		no_food_message = true;
		prevTime_talk = getCurrentTime();
	}
	food_menu = false;
	hideFoodButton();
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeBattle(JNIEnv*, jobject)
{
	if(pet_BP>0){
	   pet_BP -= 10;
	   hideMainButton();
	   showShotButton();
	   main_menu = false;
	   face_change_count = 0;
	   shotgun_init = true;
	}
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeFire(JNIEnv*, jobject)
{
	shotgun_isShot = true;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeAdv(JNIEnv*, jobject)
{
    hideMainButton();
	showAdvInterface();
	main_menu = false;
	face_change_count = 0;
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeShootGameStart(JNIEnv*, jobject)
{
	if(pet_BP>0){
	   pet_BP -= 10;
	   shootemup_init = true;
	   hideAdvInterface();
	}
	else{
		showMainButton();
		hideAdvInterface();
		main_menu = true;
		prevTime_talk = getCurrentTime();
	}
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeMoneyGameStart(JNIEnv*, jobject)
{
	moneydown_init = true;
	hideAdvInterface();

/*	showMainButton();
	hideAdvInterface();
	main_menu = true;
	prevTime_talk = getCurrentTime();*/
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeAdvClosed(JNIEnv*, jobject)
{
	showMainButton();
	hideAdvInterface();
	main_menu = true;
	prevTime_talk = getCurrentTime();
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeShop(JNIEnv*, jobject)
{
	ShopActive = true;
	showShopInterface();
	hideMainButton();
	main_menu = false;
	face_change_count = 0;

	if( Skin_equip_normal == TEXTURE_NORMAL3 ){
		showUseCat();
		showSkinRabbit();
		if(buy_bear)
			showSkinBear();
	}
	else if( Skin_equip_normal == TEXTURE_NORMAL2 ){
		showUseBear();
		showSkinRabbit();
		if(buy_cat)
			showSkinCat();
	}
	else if( Skin_equip_normal == TEXTURE_NORMAL1 ){
		if(buy_cat)
			showSkinCat();
		if(buy_bear)
			showSkinBear();
	}

	if( arm_equip_type == TEXTURE_BULLET_ARROW ){
		if(buy_bullet1)
			showBullet1();
		if(buy_bullet2)
			showBullet2();
	}
	else if( arm_equip_type == TEXTURE_BULLET_LV2 ){
		showUseBullet1();
		showArrow();
		if(buy_bullet2)
			showBullet2();
	}
	else if( arm_equip_type == TEXTURE_BULLET_LV3 ){
		showUseBullet2();
		showArrow();
		if(buy_bullet1)
			showBullet1();
	}
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeUseCat(JNIEnv*, jobject)
{
	if(total_money >= CAT_PRICE){
		total_money -= CAT_PRICE;
		buy_cat = true;
		//sound of money
		playSoundEffect( BUYING_SOUND, 0.6 );
	}
	else if(buy_cat == false){
		//sound of X
		playSoundEffect( NOMONEY_SOUND, 0.7 );
	}
	if(buy_cat){
		Skin_equip_normal = TEXTURE_NORMAL3;
		Skin_equip_eat    = TEXTURE_EAT3;
		Skin_equip_hurt   = TEXTURE_HURT3;
		Skin_equip_smile  = TEXTURE_SMILE3;
		Skin_equip_die    = TEXTURE_DIE3;

		buy_cat = true;
		showUseCat();
		showSkinRabbit();
		if(buy_bear)
			showSkinBear();
		//sound of equip
		playSoundEffect( USE_SOUND, 0.6 );
	}
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeUseBear(JNIEnv*, jobject)
{
	if(total_money >= BEAR_PRICE){
		total_money -= BEAR_PRICE;
		buy_bear = true;
		//sound of money
		playSoundEffect( BUYING_SOUND, 0.6 );
	}
	else if(buy_bear == false){
		//sound of X
		playSoundEffect( NOMONEY_SOUND, 0.7 );
	}

	if(buy_bear){
		Skin_equip_normal = TEXTURE_NORMAL2;
		Skin_equip_eat    = TEXTURE_EAT2;
		Skin_equip_hurt   = TEXTURE_HURT2;
		Skin_equip_smile  = TEXTURE_SMILE2;
		Skin_equip_die    = TEXTURE_DIE2;

		showUseBear();
		showSkinRabbit();
		if(buy_cat)
			showSkinCat();
		//sound of equip
		playSoundEffect( USE_SOUND, 0.6 );
	}
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeUseRabbit(JNIEnv*, jobject)
{
    Skin_equip_normal = TEXTURE_NORMAL1;
	Skin_equip_eat    = TEXTURE_EAT1;
	Skin_equip_hurt   = TEXTURE_HURT1;
	Skin_equip_smile  = TEXTURE_SMILE1;
	Skin_equip_die    = TEXTURE_DIE1;

	showUseRabbit();
	if(buy_cat)
	  showSkinCat();
	if(buy_bear)
	  showSkinBear();

	playSoundEffect( USE_SOUND, 0.6 );
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeUseArrow(JNIEnv*, jobject)
{
	arm_equip_type = TEXTURE_BULLET_ARROW;
	showUseArrow();
	if(buy_bullet1)
	  showBullet1();
	if(buy_bullet2)
	  showBullet2();

	playSoundEffect( USE_SOUND, 0.6 );
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeUseBullet1(JNIEnv*, jobject)
{
	if( total_money >= BULLET1_PRICE ){
		total_money -= BULLET1_PRICE;
		//sound of money
		playSoundEffect( BUYING_SOUND, 0.6 );
		buy_bullet1 = true;
	}
	else if(buy_bullet1 == false){
		//sound of X
		playSoundEffect( NOMONEY_SOUND, 0.7 );
	}
	if(buy_bullet1){
		arm_equip_type = TEXTURE_BULLET_LV2;
		showUseBullet1();

		if(buy_bullet2)
			showBullet2();
		showArrow();
		//sound of equip
		playSoundEffect( USE_SOUND, 0.6 );
	}
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeUseBullet2(JNIEnv*, jobject)
{
	if( total_money >= BULLET2_PRICE ){
		total_money -= BULLET2_PRICE;
		buy_bullet2 = true;
		//sound of money
		playSoundEffect( BUYING_SOUND, 0.6 );
	}
	else if(buy_bullet2 == false){
		//sound of X
		playSoundEffect( NOMONEY_SOUND, 0.7 );
	}
	if(buy_bullet2){
		arm_equip_type = TEXTURE_BULLET_LV3;
		showUseBullet2();

		if(buy_bullet1)
			showBullet1();
		showArrow();
		//sound of equip
		playSoundEffect( USE_SOUND, 0.6 );
	}
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeBuyBerry(JNIEnv*, jobject)
{
	if( total_money >= BERRY_PRICE ){
		total_money -= BERRY_PRICE;
		berryHolding += 1;
		//sound of money
		playSoundEffect( BUYING_SOUND, 0.6 );
	}
	else{
		//sound of X
		playSoundEffect( NOMONEY_SOUND, 0.7 );
	}
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeBuyCheese(JNIEnv*, jobject)
{
	if( total_money >= CHEESE_PRICE ){
		total_money -= CHEESE_PRICE;
		cheeseHolding += 1;
		//sound of money
		playSoundEffect( BUYING_SOUND, 0.6 );
	}
	else{
		//sound of X
		playSoundEffect( NOMONEY_SOUND, 0.7 );
	}
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeShopClosed(JNIEnv*, jobject)
{
	ShopActive = false;
	hideShopInterface();
	showMainButton();
	main_menu = true;
	prevTime_talk = getCurrentTime();
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_setActivityPortraitMode(JNIEnv *, jobject, jboolean isPortrait)
{
    isActivityInPortraitMode = isPortrait;
}


JNIEXPORT int JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_initTracker(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_initTracker");

    // Initialize the image tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::Tracker* tracker = trackerManager.initTracker(QCAR::Tracker::IMAGE_TRACKER);
    if (tracker == NULL)
    {
        LOG("Failed to initialize ImageTracker.");
        return 0;
    }

    LOG("Successfully initialized ImageTracker.");
    return 1;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_deinitTracker(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_deinitTracker");

    // Deinit the image tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    trackerManager.deinitTracker(QCAR::Tracker::IMAGE_TRACKER);
}


JNIEXPORT int JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_loadTrackerData(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_loadTrackerData");
    
    // Get the image tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::ImageTracker* imageTracker = static_cast<QCAR::ImageTracker*>(trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER));
    if (imageTracker == NULL)
    {
        LOG("Failed to load tracking data set because the ImageTracker has not"
            " been initialized.");
        return 0;
    }

    // Create the data set:
    dataSet = imageTracker->createDataSet();
    if (dataSet == 0)
    {
        LOG("Failed to create a new tracking data.");
        return 0;
    }

    // Load the data set:
    if (!dataSet->load("FlakesBox.xml", QCAR::DataSet::STORAGE_APPRESOURCE))
    {
        LOG("Failed to load data set.");
        return 0;
    }

    LOG("Successfully loaded the data set.");
    return 1;
}


JNIEXPORT int JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_destroyTrackerData(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_destroyTrackerData");

    // Get the image tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::ImageTracker* imageTracker = static_cast<QCAR::ImageTracker*>(trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER));
    if (imageTracker == NULL)
    {
        LOG("Failed to destroy the tracking data set because the ImageTracker has not"
            " been initialized.");
        return 0;
    }

    if (dataSet != 0)
    {
        if (!imageTracker->deactivateDataSet(dataSet))
        {
            LOG("Failed to destroy the tracking data set because the data set "
                "could not be deactivated.");
            return 0;
        }

        if (!imageTracker->destroyDataSet(dataSet))
        {
            LOG("Failed to destroy the tracking data set.");
            return 0;
        }

        LOG("Successfully destroyed the data set.");
        dataSet = 0;
        mit = 0;
        return 1;
    }

    LOG("No tracker data set to destroy.");
    return 0;
}


JNIEnv*
getJNIEnv() {
    JNIEnv* env;
    if (javaVM == NULL || javaVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        return NULL;
    }

    return env;
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_onQCARInitializedNative(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_onQCARInitializedNative");

    // Validate the MultiTarget and setup programmatically if required:
    initMIT();

    // Get the image tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::ImageTracker* imageTracker = static_cast<QCAR::ImageTracker*>(trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER));

    // Activate the data set:
    if (!imageTracker->activateDataSet(dataSet))
    {
        LOG("Failed to activate data set.");
        return;
    }

    LOG("Successfully activated the data set.");

    jmethod_playSoundEffect  = NULL;

    jmethod_showMainButton   = NULL;
    jmethod_hideMainButton   = NULL;
    jmethod_showFoodButton   = NULL;
    jmethod_hideFoodButton   = NULL;

    jmethod_showShopInterface= NULL;
    jmethod_hideShopInterface= NULL;

    jmethod_showUseCat       = NULL;
    jmethod_showUseRabbit    = NULL;
    jmethod_showUseBear      = NULL;
    jmethod_showSkinCat      = NULL;
    jmethod_showSkinRabbit   = NULL;
    jmethod_showSkinBear     = NULL;

    jmethod_showUseArrow     = NULL;
    jmethod_showUseBullet1   = NULL;
    jmethod_showUseBullet2   = NULL;
    jmethod_showArrow   	 = NULL;
    jmethod_showBullet1  	 = NULL;
    jmethod_showBullet2		 = NULL;

    jmethod_enableBuyBerry   = NULL;
    jmethod_enableBuyCheese  = NULL;
    jmethod_cannotBuyBerry   = NULL;
    jmethod_cannotBuyCheese  = NULL;

    jmethod_showAdvInterface = NULL;
    jmethod_hideAdvInterface = NULL;

    jmethod_showShotButton   = NULL;

    jmethod_transmitData     = NULL;
    jmethod_displayMessage   = NULL;

    QCAR::registerCallback(&myUpdateCallBack);
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargetsRenderer_initNativeCallback(JNIEnv* env, jobject obj)
{
    // Store the calling object for later use
    // Make a global reference to keep it valid beyond the scope of this function
    activityObj = env->NewGlobalRef(obj);

    // Store the class of the calling object for later use
    jclass objClass = env->GetObjectClass(obj);
    activityClass = (jclass) env->NewGlobalRef(objClass);

    // Store class method IDs for later use
    JNIEnv* jniEnv = getJNIEnv();
    jmethod_playSoundEffect  = jniEnv->GetMethodID(activityClass, "playSoundEffect", "(IF)V");

    jmethod_showMainButton   = jniEnv->GetMethodID(activityClass, "showMainButton", "()V");
    jmethod_hideMainButton 	 = jniEnv->GetMethodID(activityClass, "hideMainButton", "()V");
    jmethod_showFoodButton   = jniEnv->GetMethodID(activityClass, "showFoodButton", "()V");
    jmethod_hideFoodButton   = jniEnv->GetMethodID(activityClass, "hideFoodButton", "()V");
    jmethod_showAdvInterface = jniEnv->GetMethodID(activityClass, "showAdvInterface", "()V");
    jmethod_hideAdvInterface = jniEnv->GetMethodID(activityClass, "hideAdvInterface", "()V");

    jmethod_showShopInterface= jniEnv->GetMethodID(activityClass, "showShopInterface", "()V");
    jmethod_hideShopInterface= jniEnv->GetMethodID(activityClass, "hideShopInterface", "()V");
    jmethod_showUseCat       = jniEnv->GetMethodID(activityClass, "showUseCat", "()V");
    jmethod_showUseRabbit    = jniEnv->GetMethodID(activityClass, "showUseRabbit", "()V");
    jmethod_showUseBear      = jniEnv->GetMethodID(activityClass, "showUseBear", "()V");
    jmethod_showSkinCat      = jniEnv->GetMethodID(activityClass, "showSkinCat", "()V");
    jmethod_showSkinRabbit   = jniEnv->GetMethodID(activityClass, "showSkinRabbit", "()V");
    jmethod_showSkinBear     = jniEnv->GetMethodID(activityClass, "showSkinBear", "()V");

    jmethod_showUseArrow     = jniEnv->GetMethodID(activityClass, "showUseArrow", "()V");
    jmethod_showUseBullet1   = jniEnv->GetMethodID(activityClass, "showUseBullet1", "()V");
    jmethod_showUseBullet2   = jniEnv->GetMethodID(activityClass, "showUseBullet2", "()V");
    jmethod_showArrow   	 = jniEnv->GetMethodID(activityClass, "showArrow", "()V");
    jmethod_showBullet1  	 = jniEnv->GetMethodID(activityClass, "showBullet1", "()V");
    jmethod_showBullet2		 = jniEnv->GetMethodID(activityClass, "showBullet2", "()V");

    jmethod_enableBuyBerry   = jniEnv->GetMethodID(activityClass, "enableBuyBerry", "()V");
    jmethod_enableBuyCheese  = jniEnv->GetMethodID(activityClass, "enableBuyCheese", "()V");
    jmethod_cannotBuyBerry   = jniEnv->GetMethodID(activityClass, "cannotBuyBerry", "()V");
    jmethod_cannotBuyCheese  = jniEnv->GetMethodID(activityClass, "cannotBuyCheese", "()V");

    jmethod_showShotButton   = jniEnv->GetMethodID(activityClass, "showShotButton", "()V");
    jmethod_displayMessage   = jniEnv->GetMethodID(activityClass, "displayMessage", "(Ljava/lang/String;)V");
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_dataEditor(JNIEnv* env, jobject obj){

	activityObj = env->NewGlobalRef(obj);

    jclass objClass = env->GetObjectClass(obj);
    activityClass = (jclass) env->NewGlobalRef(objClass);

    JNIEnv* jniEnv = getJNIEnv();
    jmethod_transmitData = jniEnv->GetMethodID(activityClass, "transmitData", "(IIIZZIIIZZI)V");

	transmitData(total_money, top_score, pet_BP, buy_cat, buy_bear, Skin_equip_normal, berryHolding, cheeseHolding, buy_bullet1, buy_bullet2, arm_equip_type);
}

void
playSoundEffect(int soundIndex, float volume)
{
    getJNIEnv()->CallVoidMethod(activityObj, jmethod_playSoundEffect, soundIndex, volume);
}

void
showMainButton()
{
    getJNIEnv()->CallVoidMethod(activityObj, jmethod_showMainButton);
}

void
hideMainButton()
{
    getJNIEnv()->CallVoidMethod(activityObj, jmethod_hideMainButton);
}

void
showFoodButton()
{
    getJNIEnv()->CallVoidMethod(activityObj, jmethod_showFoodButton);
}

void
hideFoodButton()
{
    getJNIEnv()->CallVoidMethod(activityObj, jmethod_hideFoodButton);
}

void
showAdvInterface()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showAdvInterface);
}

void
hideAdvInterface()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_hideAdvInterface);
}


void
showShopInterface()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showShopInterface);
}

void
hideShopInterface()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_hideShopInterface);
}

void
showUseCat()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showUseCat);
}

void
showUseRabbit()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showUseRabbit);
}

void
showUseBear()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showUseBear);
}

void
showSkinCat()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showSkinCat);
}

void
showSkinRabbit()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showSkinRabbit);
}

void
showSkinBear()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showSkinBear);
}

void showUseArrow()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showUseArrow);
}

void showUseBullet1()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showUseBullet1);
}

void showUseBullet2()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showUseBullet2);
}

void showArrow()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showArrow);
}

void showBullet1()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showBullet1);
}

void showBullet2()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showBullet2);
}

void enableBuyBerry()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_enableBuyBerry);
}

void enableBuyCheese()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_enableBuyCheese);
}

void cannotBuyBerry()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_cannotBuyBerry);
}

void cannotBuyCheese()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_cannotBuyCheese);
}


void
showShotButton()
{
	getJNIEnv()->CallVoidMethod(activityObj, jmethod_showShotButton);
}


void
transmitData(int money_SaveData, int score_SaveData, int BP_SaveData, bool cat_SaveData, bool bear_SaveData,
		     int pet_Type, int berry_SaveData, int cheese_SaveData,	bool bullet1_Data, bool bullet2_Data, int arm_Type)
{
    // Call a Java method that transit data back to from C to Java
    jint jm = money_SaveData;
    jint jsc = score_SaveData;
    jint jbp = BP_SaveData;
    jboolean jcat = cat_SaveData;
    jboolean jbear = bear_SaveData;
    jint jskin = pet_Type;
    jint jberry = berry_SaveData;
    jint jcheese = cheese_SaveData;
    jboolean jbullet1 = bullet1_Data;
    jboolean jbullet2 = bullet2_Data;
    jint jarm = arm_Type;
    getJNIEnv()->CallVoidMethod(activityObj, jmethod_transmitData, jm, jsc, jbp, jcat, jbear, jskin, jberry, jcheese, jbullet1, jbullet2, jarm);
}

void
displayMessage(char* message)
{
    // Call a Java method that displays a message via a toast
    JNIEnv* jniEnv = getJNIEnv();
    jstring js = jniEnv->NewStringUTF(message);
    jniEnv->CallVoidMethod(activityObj, jmethod_displayMessage, js);
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargetsRenderer_renderFrame(JNIEnv *, jobject)
{
    //LOG("Java_com_qualcomm_QCARSamples_MultiTargets_GLRenderer_");
    SampleUtils::checkGlError("Check gl errors prior render Frame");

    // Clear color and depth buffer 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get the state from QCAR and mark the beginning of a rendering section
    QCAR::State state = QCAR::Renderer::getInstance().begin();

    // Explicitly render the Video Background
    QCAR::Renderer::getInstance().drawVideoBackground();
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Did we find any trackables this frame?
    if ( state.getNumTrackableResults() > 0 )
    {
    	display_message = false;

        // Get the trackable:
        const QCAR::TrackableResult* result=NULL;
        int numResults=state.getNumTrackableResults();

        // Browse results searching for the MultiTarget
        for (int j=0;j<numResults;j++)
        {
            result = state.getTrackableResult(j);
            if (result->getType() == QCAR::TrackableResult::MULTI_TARGET_RESULT) {
            	break;
            }
            result=NULL;
        }

        // If it was not found exit
        if (result==NULL)
        {
            // Clean up and leave
            glDisable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);

            QCAR::Renderer::getInstance().end();
            return;
        }

        if(init_status){
        	if( Skin_equip_normal == TEXTURE_NORMAL3 ){   //cat
        		Skin_equip_eat    = TEXTURE_EAT3;
        		Skin_equip_hurt   = TEXTURE_HURT3;
        		Skin_equip_smile  = TEXTURE_SMILE3;
        		Skin_equip_die    = TEXTURE_DIE3;
        	}
        	else if (Skin_equip_normal == TEXTURE_NORMAL2){  //bear
        		Skin_equip_eat    = TEXTURE_EAT2;
        		Skin_equip_hurt   = TEXTURE_HURT2;
        		Skin_equip_smile  = TEXTURE_SMILE2;
        		Skin_equip_die    = TEXTURE_DIE2;
        	}
        	else if(Skin_equip_normal == TEXTURE_NORMAL1){  //rabbit
        		Skin_equip_eat    = TEXTURE_EAT1;
        		Skin_equip_hurt   = TEXTURE_HURT1;
        		Skin_equip_smile  = TEXTURE_SMILE1;
        		Skin_equip_die    = TEXTURE_DIE1;
        	}

        	init_status = false;
        }
                
        QCAR::Matrix44F modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());

        QCAR::Matrix44F modelViewProjection;
        SampleUtils::scalePoseMatrix(kCubeScaleX, kCubeScaleY, kCubeScaleZ, &modelViewMatrix.data[0]);
        SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);

        glUseProgram(shaderProgramID);
         
        // Draw the cube:

        BOUNDINGBOX cubebox;
        createBoundingBox( &cubebox, cubeVertices, NUM_CUBE_VERTEX);
        calculateBoundingBox(&cubebox, modelViewMatrix);

        //__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "cube1 : xmin: %f, xmax: %f, ymin: %f, ymax: %f, zmin: %f, zmax: %f", cubebox.xmin,cubebox.xmax,cubebox.ymin,cubebox.ymax,cubebox.zmin,cubebox.zmax);
        //__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "cube : xmin: %f, xmax: %f, ymin: %f, ymax: %f, zmin: %f, zmax: %f", cubebox.xmin,cubebox.xmax,cubebox.ymin,cubebox.ymax,cubebox.zmin,cubebox.zmax);

        // We must detect if background reflection is active and adjust the culling direction.
        // If the reflection is active, this means the post matrix has been reflected as well,
        // therefore standard counter clockwise face culling will result in "inside out" models.
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        if(QCAR::Renderer::getInstance().getVideoBackgroundConfig().mReflection == QCAR::VIDEO_BACKGROUND_REFLECTION_ON)
            glFrontFace(GL_CW);  //Front camera
        else
            glFrontFace(GL_CCW);   //Back camera

        glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeVertices[0]);
        glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeNormals[0]);
        glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeTexCoords[0]);
        
        glEnableVertexAttribArray(vertexHandle);
        glEnableVertexAttribArray(normalHandle);
        glEnableVertexAttribArray(textureCoordHandle);

        int Skin_equip = Skin_equip_normal;
        if(isEat)
        	Skin_equip = Skin_equip_eat;
        else if(isSmile)
        	Skin_equip = Skin_equip_smile;
        else if(isDie)
        	Skin_equip = Skin_equip_die;
        else if(isHurt)
        	Skin_equip = Skin_equip_hurt;
        else if(isTalk)
        	Skin_equip = Skin_equip_smile;
        else
        	Skin_equip = Skin_equip_normal;

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, textures[Skin_equip]->mTextureID);
        glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&modelViewProjection.data[0] );
        glUniform1i(texSampler2DHandle, 0 /*GL_TEXTURE0*/);
        glDrawElements(GL_TRIANGLES, NUM_CUBE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &cubeIndices[0]);

        glDisable(GL_CULL_FACE);

        // control time of facial expression
        static double prevTime_eat;
        static double prevTime_smile;
        static double prevTime_hurt;
        static double prevTime_die;
        static double prevTime_talkface;

        if(isEat){
            double time = getCurrentTime();
            float dt_eat = (float)(time-prevTime_eat);
            if(dt_eat > 0.5){
            	isEat = false;
            	showMainButton();
            	main_menu = true;
            	prevTime_talk = getCurrentTime();
        	}
        }
        else if(isSmile){
        	double currTime_smile = getCurrentTime();
        	float dt_smile = (float)(currTime_smile - prevTime_smile);
            if(dt_smile > 0.3){
                 isSmile = false;
            }
        }
        else if(isHurt){
        	double currTime_hurt = getCurrentTime();
        	float dt_hurt = (float)(currTime_hurt - prevTime_hurt);
            if(dt_hurt > 0.5){
            	 isHurt = false;
            }
        }
        else if(isDie){
        	double currTime_die = getCurrentTime();
        	float dt_die = (float)(currTime_die - prevTime_die);
            if(dt_die > 2.0){
            	isDie = false;
            }
        }
        else if(isTalk){
            double currTime_talkface = getCurrentTime();
            float dt_talkface = (float)(currTime_talkface - prevTime_talkface);
            if(dt_talkface > 2.0){
               isTalk = false;
            }
        }


        if(!modelPoseIsStatic){
        	modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
            SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
            stableModelViewProjection = modelViewProjection;
            modelPoseIsStatic = true;
        } else {
        	modelViewProjection = stableModelViewProjection;
        }


        if(main_menu){
        	glDisable(GL_DEPTH_TEST);
        	srand(time(0));

        	// BP Bar
        	float bp_lengh = (float)pet_BP/50.0 * 60.0;
        	modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
            SampleUtils::rotatePoseMatrix( 180.0f, 1.0f, 0.0f, 0.0f, &modelViewMatrix.data[0]);
            SampleUtils::scalePoseMatrix( bp_lengh, 9.6, 0.0, &modelViewMatrix.data[0]);
        	// adjust the position of the bar to align frame
        	SampleUtils::translatePoseMatrix( -( ( 60.0-bp_lengh )/( 2.0*bp_lengh ) ), -9.05f, 0.0f, &modelViewMatrix.data[0]);
        	SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        	draw2DPicture( TEXTURE_BP_BAR, modelViewProjection );

        	modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
            SampleUtils::rotatePoseMatrix( 180.0f, 1.0f, 0.0f, 0.0f, &modelViewMatrix.data[0]);
            SampleUtils::scalePoseMatrix( 60.0, 9.6, 0.0, &modelViewMatrix.data[0]);
        	SampleUtils::translatePoseMatrix( 0.0f, -9.0f, 0.0f, &modelViewMatrix.data[0]);
        	SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        	draw2DPicture( TEXTURE_BP_FRAME, modelViewProjection );

        	// Pet message
        	double currTime_talk = getCurrentTime();
        	float dt_talk = (float)(currTime_talk - prevTime_talk);

        	if( dt_talk > 11 ){    // reset timer
        		prevTime_talk = getCurrentTime();
        		face_change_count = 0;
        	}
        	else if( dt_talk > 6 ){  // still 6 sec.
        		if( face_change_count <  3 )
        		 	face_change_count++;

        		if( face_change_count == 1 ){
          			isTalk = true;
           			prevTime_talkface = getCurrentTime();
           			if(pet_BP <= 10)
           			   message_type = TEXTURE_HUNGRY_MESSAGE;
           			else if(pet_BP <= 20)
           			   message_type = ( rand() % 3 ) + TEXTURE_HUNGRY_MESSAGE;
           			else
           			   message_type = ( rand() % 2 + 1 ) + TEXTURE_HUNGRY_MESSAGE;
           		}
        		modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
        		SampleUtils::rotatePoseMatrix( 180.0f, 1.0f, 0.0f, 0.0f, &modelViewMatrix.data[0]);
        		SampleUtils::scalePoseMatrix( 84.0, 21.9, 0.0, &modelViewMatrix.data[0]);
        		SampleUtils::translatePoseMatrix( 2.0f, -5.0f, 0.0f, &modelViewMatrix.data[0]);
        		SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        		draw2DPicture( message_type, modelViewProjection );
        	}
        	else{     //  other status
        		if( no_food_message && dt_talk < 5 ){
        			modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
        			SampleUtils::rotatePoseMatrix( 180.0f, 1.0f, 0.0f, 0.0f, &modelViewMatrix.data[0]);
        			SampleUtils::scalePoseMatrix( 73.56, 36.48, 0.0, &modelViewMatrix.data[0]);
        			SampleUtils::translatePoseMatrix( 1.7f, -4.0f, 0.0f, &modelViewMatrix.data[0]);
        			SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        			draw2DPicture( MESSAGE_NO_FOOD, modelViewProjection );
        		}
        		else if( no_food_message ){
        			prevTime_talk = getCurrentTime();
        			no_food_message = false;
        		}
        		face_change_count = 0;
        	}

        	// TOP SCORE
        	 loadIdentity(modelViewMatrix);
             SampleUtils::translatePoseMatrix( -0.76f, -0.55f, 2.0f, &modelViewMatrix.data[0]);
             SampleUtils::scalePoseMatrix(0.252, 0.052, 0.0, &modelViewMatrix.data[0]);
        	 SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        	 draw2DPicture(TEXTURE_BEST_SCORE, modelViewProjection);
        	 NumberDisplay( top_score , 0.48, 0.55, modelViewMatrix, modelViewProjection);

        	 // money
        	 loadIdentity(modelViewMatrix);
             SampleUtils::translatePoseMatrix( -0.90f, 0.51f, 2.0f, &modelViewMatrix.data[0]);
             SampleUtils::scalePoseMatrix(0.08, 0.08, 0.0, &modelViewMatrix.data[0]);
        	 SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        	 draw2DPicture(TEXTURE_MONEY_ICON, modelViewProjection);
        	 NumberDisplay( total_money, 0.73, -0.50, modelViewMatrix, modelViewProjection);
        }

        // Feed System
        if(food_menu){
        	Skin_equip = Skin_equip_normal; // avoid to laugh

        	loadIdentity(modelViewMatrix);
        	SampleUtils::translatePoseMatrix( -0.60f, -0.18f, 2.0f, &modelViewMatrix.data[0]);
        	SampleUtils::scalePoseMatrix(0.04, 0.04, 0.0, &modelViewMatrix.data[0]);
        	SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        	draw2DPicture(TEXTURE_MULTIPLY_ICON, modelViewProjection);

        	loadIdentity(modelViewMatrix);
        	SampleUtils::translatePoseMatrix( -0.60f, -0.44f, 2.0f, &modelViewMatrix.data[0]);
        	SampleUtils::scalePoseMatrix(0.04, 0.04, 0.0, &modelViewMatrix.data[0]);
        	SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
        	draw2DPicture(TEXTURE_MULTIPLY_ICON, modelViewProjection);

        	NumberDisplay(berryHolding, 0.50, 0.19, modelViewMatrix, modelViewProjection);
            NumberDisplay(cheeseHolding, 0.50, 0.45, modelViewMatrix, modelViewProjection);
        }

        if( FoodActive ){

        	glEnable(GL_DEPTH_TEST);
          	for(int j = 0; j < 16; ++j) {
               if((j != 14))
                  modelViewMatrix.data[j] = 0.0f;
               if(j % 5 == 0)
                  modelViewMatrix.data[j] = 1.0f;
            }
        	SampleUtils::translatePoseMatrix(200.0f, -100.5f, 0.0f, &modelViewMatrix.data[0]);
        	SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);

        	BOUNDINGBOX objectbox;
        	createBoundingBox( &objectbox, cheeseVertices, NUM_CHEESE_VERTEX );

        	BOUNDINGBOX objectbox2;
        	createBoundingBox( &objectbox2, berryVertices, NUM_BERRY_VERTEX );

        	calculateBoundingBox(&objectbox, modelViewMatrix);
        	calculateBoundingBox(&objectbox2, modelViewMatrix);

        	if( call_cheese )
                isEat = BoundingBoxIntersect(cubebox, objectbox);
        	else if( call_strawberry )
        		isEat = BoundingBoxIntersect(cubebox, objectbox2);

        	if( !isEat && call_cheese ){
        		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cheeseVertices[0]);
        		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cheeseNormals[0]);
        		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cheeseTexCoords[0]);

        		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_CHEESE]->mTextureID);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        		glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&modelViewProjection.data[0]);
        		glDrawElements(GL_TRIANGLES, NUM_CHEESE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &cheeseIndices[0]);
        	}
        	else if( !isEat && call_strawberry ){
        		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &berryVertices[0]);
        		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &berryNormals[0]);
        		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &berryTexCoords[0]);

        		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BERRY]->mTextureID);
        	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        		glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&modelViewProjection.data[0]);
        		glDrawElements(GL_TRIANGLES, NUM_BERRY_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &berryIndices[0]);
        	}
        	else {
        		FoodActive = false;
        		glDisable(GL_DEPTH_TEST);
        		if(call_strawberry){
            	   call_strawberry = false;
            	   playSoundEffect( SLURP_SOUND, 0.8);
            	   if(pet_BP<50)
            	     pet_BP += 15;
            	   if(pet_BP>50)
            		 pet_BP = 50;
        		}
        		else if(call_cheese){
        		   call_cheese = false;
        		   playSoundEffect( SMILE_SOUND, 0.8);
        		   if(pet_BP<50)
        		     pet_BP += 10;
            	   if(pet_BP>50)
            		 pet_BP = 50;
        		}
        		prevTime_eat = getCurrentTime();
        	}
        }

        if( ShopActive ){
        	// Distinguish the amount of money
        	if( total_money < BERRY_PRICE)
        	    cannotBuyBerry();
        	else
        		enableBuyBerry();

        	if( total_money < CHEESE_PRICE)
        		cannotBuyCheese();
        	else
        		enableBuyCheese();
        }

        static double prev_time_game;
        static double prev_time_add_bomb;
        static float accel = 1.0;
        static float interval = 1.0;

        if (moneydown_init) {
           for(int i = 0; i < 10; ++i) {
               bomb[i].isActive = false;
           }
            collected_money = 0;
            pet_money_HP = 3;
          	bombcount = 0;
          	moneydown_start = true;
           	prev_time_game = getCurrentTime();
           	prev_time_add_bomb = prev_time_game;
           	moneydown_init = false;
           	srand(time(0));
        }

        if (moneydown_start) {
        	glEnable(GL_DEPTH_TEST);
           	double cur_time_game = getCurrentTime();
            float dt_game = (float) (cur_time_game - prev_time_game);
            float dt_add_bomb = (float)(cur_time_game - prev_time_add_bomb);

             // adding new bomb
           	if ( dt_add_bomb > interval ) {
           		bomb[bombcount].height = -200.0;
           		bomb[bombcount].angle = 0.0;
          		bomb[bombcount].pos = (float)(rand() % 400 - 200);
                bomb[bombcount].isActive = true;
                bomb[bombcount].isBomb = !(rand() % 3);
                bombcount = (bombcount + 1) % 10;
                prev_time_add_bomb = cur_time_game;
                interval = accel + (float)(rand() % 200 - 100) / 100.0;
                //__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "%f", interval);
            }

            for(int i = 0; i < 10; ++i) {
                if(bomb[i].isActive) {
                	bomb[i].height += dt_game * 120.0;

                	if( bomb[i].angle < 360.0 )
                		bomb[i].angle += dt_game * 200;
                	else
                		bomb[i].angle -= 360.0;

              		// matrix for bombs
                   	modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());

                   	for(int j = 0; j < 16; ++j) {
                   		if((j != 14))
                    		modelViewMatrix.data[j] = 0.0f;
                       	if(j % 5 == 0)
                        	modelViewMatrix.data[j] = 1.0f;
                    }

                	SampleUtils::translatePoseMatrix(bomb[i].pos, bomb[i].height, 0.0f, &modelViewMatrix.data[0]);
                 	SampleUtils::rotatePoseMatrix(-bomb[i].angle, 1.0f, 0, 0, &modelViewMatrix.data[0]);
                	SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);

                	if( bomb[i].isBomb ){
                		 // bounding box for bombs
                		createBoundingBox(&bomb[i].bb, bombVertices, NUM_BOMB_VERTEX);
                		calculateBoundingBox(&bomb[i].bb, modelViewMatrix);
                        if(BoundingBoxIntersect(cubebox, bomb[i].bb)){
                     	  bomb[i].isActive = false;
                     	  playSoundEffect( BOMB_SOUND, 0.9 );
                           pet_money_HP -=1;
                           isHurt = true;
                           prevTime_hurt = getCurrentTime();
                        }

                 	    glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &bombVertices[0]);
                 	    glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &bombNormals[0]);
                 	    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &bombTexCoords[0]);

                 	    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_TACHAS]->mTextureID);
                 	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                 	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                 	    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&modelViewProjection.data[0]);
                 	    glDrawElements(GL_TRIANGLES, NUM_BOMB_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &bombIndices[0]);
                    }
                	else{
                		createBoundingBox(&bomb[i].bb, coinVertices, NUM_COIN_VERTEX);

                		calculateBoundingBox(&bomb[i].bb, modelViewMatrix);
                        if(BoundingBoxIntersect(cubebox, bomb[i].bb)){
                     	  bomb[i].isActive = false;
                     	  playSoundEffect( COIN_SOUND, 0.7 );
                     	  isSmile = true;
                     	  collected_money++;
                          if(isHurt)
                       	     isHurt = false;
                          prevTime_smile = getCurrentTime();
                    }

                 	    glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &coinVertices[0]);
                 	    glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &coinNormals[0]);
                 	    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &coinTexCoords[0]);

                 	    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_COIN]->mTextureID);
                 	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                 	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                 	    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&modelViewProjection.data[0]);
                 	    glDrawElements(GL_TRIANGLES, NUM_COIN_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &coinIndices[0]);
                	}
                }
            }

            //display money
            loadIdentity(modelViewMatrix);
            SampleUtils::translatePoseMatrix( -0.82f, -0.55f, 2.0f, &modelViewMatrix.data[0]);
            SampleUtils::scalePoseMatrix(0.164, 0.059, 0.0, &modelViewMatrix.data[0]);
            SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
            draw2DPicture(TEXTURE_MONEY, modelViewProjection);
            NumberDisplay( collected_money , 0.58, 0.55, modelViewMatrix, modelViewProjection);


            if( pet_money_HP == 0 ){
            	total_money += collected_money;
                showMainButton();
                main_menu = true;
                prevTime_talk = getCurrentTime();
                moneydown_start = false;
            }
            if( pet_money_HP >= 1 ){
              loadIdentity(modelViewMatrix);
              SampleUtils::translatePoseMatrix( -0.9f, 0.5f, 2.0f, &modelViewMatrix.data[0]);
              SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
              SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
              draw2DPicture(TEXTURE_HEART, modelViewProjection);
            }
            if( pet_money_HP >= 2 ){
              loadIdentity(modelViewMatrix);
              SampleUtils::translatePoseMatrix( -0.69f, 0.5f, 2.0f, &modelViewMatrix.data[0]);
              SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
              SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
              draw2DPicture(TEXTURE_HEART, modelViewProjection);
            }
            if( pet_money_HP >= 3 ){
              loadIdentity(modelViewMatrix);
              SampleUtils::translatePoseMatrix( -0.48f, 0.5f, 2.0f, &modelViewMatrix.data[0]);
              SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
              SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
              draw2DPicture(TEXTURE_HEART, modelViewProjection);
            }
            prev_time_game = cur_time_game;
        }

        glDisable(GL_DEPTH_TEST);
        static double shootemup_prev_time;
        static double shootemup_prev_time_new_wave;
        static double shootemup_prev_time_gun_shot;
        static double shootemup_enemy_prev_time;
        static double shootemup_prevTime_item;

        if(shootemup_init) {
             for(int i = 0; i < 5; ++i) {
               	enemy[i].isAlive = false;
             }
             for(int i = 0; i < 40; ++i) {
                bullet[i].isActive = false;
             }
              enemycount = 0;
              bulletcount = 0;
              pet_shoot_HP = 3;
              isDie = false;
              score = 0;
              shootemup_start = true;
              shootemup_enemy_prev_time = getCurrentTime();
              shootemup_prev_time = getCurrentTime();
              shootemup_prev_time_new_wave = shootemup_prev_time;
              shootemup_prev_time_gun_shot = shootemup_prev_time;
              shootemup_init = false;
              srand(time(0));
         }

         if(shootemup_start) {
             double shootemup_cur_time = getCurrentTime();
             float shootemup_dt = (float) (shootemup_cur_time - shootemup_prev_time);
             float shootemup_dt_new_wave = (float)(shootemup_cur_time - shootemup_prev_time_new_wave);
             float shootemup_dt_gun_shot = (float)(shootemup_cur_time - shootemup_prev_time_gun_shot);

             if(shootemup_dt_new_wave > 1.0) {
                modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
                enemy[enemycount].posY = modelViewMatrix.data[13] - 250.0;
                enemy[enemycount].posX = (float)(rand() % 10) * 50.0 - 250.0;
                enemy[enemycount].speedX = (modelViewMatrix.data[12] - enemy[enemycount].posX) / 2.0;
                enemy[enemycount].speedY = 125;
                enemy[enemycount].isAlive = true;
                if(enemycount > 6){ // dragon appears
                    enemy[enemycount].isDragon = (rand() % 2);
                    if(enemy[enemycount].isDragon)
                    	enemy[enemycount].hp = 25.0;
                    else
                    	enemy[enemycount].hp = 12.0;
                }
                else{
                	enemy[enemycount].hp = 12.0;
                	enemy[enemycount].isDragon = false;
                }
                enemycount = (enemycount + 1) % 10;
                shootemup_prev_time_new_wave = shootemup_cur_time;
             }

             for(int i = 0; i < 10; ++i) {
                 if(enemy[i].isAlive) {
                    enemy[i].posY += shootemup_dt * enemy[i].speedY;
                    enemy[i].posX += shootemup_dt * enemy[i].speedX;

                    // matrix for enemys
                    modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
                    for(int j = 0; j < 16; ++j) {
                       if((j != 14))
                          modelViewMatrix.data[j] = 0.0f;
                       if(j % 5 == 0)
                          modelViewMatrix.data[j] = 1.0f;
                   }
                   SampleUtils::translatePoseMatrix(enemy[i].posX, enemy[i].posY, 0.0f, &modelViewMatrix.data[0]);
                   SampleUtils::scalePoseMatrix(45.0, 22.5, 0.0, &modelViewMatrix.data[0]);
                   SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);

                   // bounding box for enemys
                   createBoundingBox(&enemy[i].bb, planeVertices, NUM_PLANE_VERTEX);
                   calculateBoundingBox(&enemy[i].bb, modelViewMatrix);

                   if(BoundingBoxIntersect(cubebox, enemy[i].bb)){
                      enemy[i].isAlive = false;
                      shootemup_hp -= 1;
                      pet_shoot_HP -= 1;
                      if(pet_shoot_HP > 0){
                    	  isHurt = true;
                         prevTime_hurt = getCurrentTime();
                         playSoundEffect( HURT_SOUND, 0.8);
                      }
                      else{
                         isDie = true;
                         isHurt = false;
                         prevTime_die = getCurrentTime();
                         playSoundEffect( DIE_SOUND, 0.6 );
                      }
                   }
                   double enemy_cur_time_state = getCurrentTime();
                   float enemy_state_dt = (float)(enemy_cur_time_state - shootemup_enemy_prev_time);
                   int texture_enemy_state;


                   if( enemy[i].isDragon ){
                	   if( enemy_state_dt < 0.15 )
                		   texture_enemy_state = TEXTURE_DRAGON_STATE1;
                   	   else if(enemy_state_dt < 0.3 )
                   		   texture_enemy_state = TEXTURE_DRAGON_STATE2;
                   	   else if(enemy_state_dt < 0.45)
                   		   texture_enemy_state = TEXTURE_DRAGON_STATE3;
                   	   else{
                   		   shootemup_enemy_prev_time = getCurrentTime();
                   		   texture_enemy_state = TEXTURE_DRAGON_STATE1;
                   	   }
                	   SampleUtils::scalePoseMatrix(1.1, 1.6, 0.0, &modelViewMatrix.data[0]);
                	   SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
                	   draw2DPicture( texture_enemy_state, modelViewProjection);
                   }
                   else{
                	   if( enemy_state_dt < 0.15 )
                		   texture_enemy_state = TEXTURE_BAT_STATE1;
                   	   else if(enemy_state_dt < 0.3 )
                   		   texture_enemy_state = TEXTURE_BAT_STATE2;
                   	   else if(enemy_state_dt < 0.45)
                   		   texture_enemy_state = TEXTURE_BAT_STATE3;
                   	   else{
                   		   shootemup_enemy_prev_time = getCurrentTime();
                   		   texture_enemy_state = TEXTURE_BAT_STATE1;
                   	   }
                	   draw2DPicture( texture_enemy_state, modelViewProjection);
                   }
                }
           }

           if(shootemup_dt_gun_shot > 0.1) {
              	// bullet_flower
              	if(bullet_flower_isActive){
              		modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
					bullet[bulletcount].posX = modelViewMatrix.data[12] - 40.0;
					bullet[bulletcount].posY = modelViewMatrix.data[13] - 45.0;
					bullet[bulletcount].speedX = 700;
					bullet[bulletcount].speedY = 400;
					bullet[bulletcount].isActive = true;

					bullet[bulletcount+1].posX = modelViewMatrix.data[12] - 15.0;
					bullet[bulletcount+1].posY = modelViewMatrix.data[13] - 45.0;
					bullet[bulletcount+1].speedX = 250;
					bullet[bulletcount+1].speedY = 500;
					bullet[bulletcount+1].isActive = true;

					bullet[bulletcount+2].posX = modelViewMatrix.data[12] + 15.0;
					bullet[bulletcount+2].posY = modelViewMatrix.data[13] - 45.0;
					bullet[bulletcount+2].speedX = -250;
					bullet[bulletcount+2].speedY = 500;
					bullet[bulletcount+2].isActive = true;

					bullet[bulletcount+3].posX = modelViewMatrix.data[12] + 40.0;
					bullet[bulletcount+3].posY = modelViewMatrix.data[13] - 45.0;
					bullet[bulletcount+3].speedX = -700;
					bullet[bulletcount+3].speedY = 400;
					bullet[bulletcount+3].isActive = true;

					bulletcount = (bulletcount + 4) % 40;
					shootemup_prev_time_gun_shot = shootemup_cur_time;
              	}
              	else{
              		modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
              		bullet[bulletcount].posX = modelViewMatrix.data[12] - 25.0;
					bullet[bulletcount].posY = modelViewMatrix.data[13] - 45.0;
					bullet[bulletcount].speedX = 0;
					bullet[bulletcount].speedY = 600;
					bullet[bulletcount].isActive = true;

					bullet[bulletcount+1].posX = modelViewMatrix.data[12] + 25.0;
					bullet[bulletcount+1].posY = modelViewMatrix.data[13] - 45.0;
					bullet[bulletcount+1].speedX = 0;
					bullet[bulletcount+1].speedY = 600;
					bullet[bulletcount+1].isActive = true;

					bulletcount = (bulletcount + 2) % 40;
					shootemup_prev_time_gun_shot = shootemup_cur_time;
              	}

                   	playSoundEffect( SHOOT_SOUND, 0.6);
           }

           for(int i = 0; i < 40; ++i) {
     	   	      if(bullet[i].isActive) {
     	   	    	  double currTime_item = getCurrentTime();
     	    		  float dt_item = (float)(currTime_item - shootemup_prevTime_item);
     	    		  if(dt_item > 3.0){
     	    			  bullet_flower_isActive = false;
     	    		  }
     	   		      // bullet_flower
				      if(bullet_flower_isActive){
				    	  bullet[i].posY -= shootemup_dt * bullet[i].speedY;
				    	  bullet[i].posX -= shootemup_dt * bullet[i].speedX;
				      }
				      else{
				    	  // bullet_normal
				    	  bullet[i].posY -= shootemup_dt * bullet[i].speedY;
				      }
				      // matrix for bullets
				      modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
                   	  for(int j = 0; j < 16; ++j) {
                          		if((j != 14))
                           		modelViewMatrix.data[j] = 0.0f;
                              	if(j % 5 == 0)
                               	modelViewMatrix.data[j] = 1.0f;
                   	  }
                   	  if(bullet_flower_isActive){
                   		  if( (i % 4) == 0 || (i % 4) == 1){
                          		SampleUtils::translatePoseMatrix(bullet[i].posX, bullet[i].posY, 0.0f, &modelViewMatrix.data[0]);
                          		//SampleUtils::rotatePoseMatrix( -45.0f, 0.0f, 0.0f, 1.0f, &modelViewMatrix.data[0]);
                          		SampleUtils::scalePoseMatrix(10.0, 20.0, 0.0, &modelViewMatrix.data[0]);
                          		SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
                   		  }
                   		  else{
                          		SampleUtils::translatePoseMatrix(bullet[i].posX, bullet[i].posY, 0.0f, &modelViewMatrix.data[0]);
                          		//SampleUtils::rotatePoseMatrix( 45.0f, 0.0f, 0.0f, 1.0f, &modelViewMatrix.data[0]);
                          		SampleUtils::scalePoseMatrix(10.0, 20.0, 0.0, &modelViewMatrix.data[0]);
                          		SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
                   		  }
                   	  }
                   	  else{
                   		SampleUtils::translatePoseMatrix(bullet[i].posX, bullet[i].posY, 0.0f, &modelViewMatrix.data[0]);
                   		SampleUtils::scalePoseMatrix(10.0, 20.0, 0.0, &modelViewMatrix.data[0]);
                   		SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
                   	  }
                           // bounding box for bullets
                   	  createBoundingBox(&bullet[i].bb, planeVertices, NUM_PLANE_VERTEX);
                   	  calculateBoundingBox(&bullet[i].bb, modelViewMatrix);

                   	  for(int j = 0; j < 10; ++j) {
                           	if(enemy[j].isAlive) {
                           		if(BoundingBoxIntersect(enemy[j].bb, bullet[i].bb)) {
                           			bullet[i].isActive = false;
                           			if(arm_equip_type == TEXTURE_BULLET_ARROW)
                           				enemy[j].hp -= 1;
                           			if(arm_equip_type == TEXTURE_BULLET_LV2)
                           			    enemy[j].hp -= 1.2;
                           			if(arm_equip_type == TEXTURE_BULLET_LV3)
                           			    enemy[j].hp -= 1.5;

                           			if(enemy[j].hp <= 0) {
                           				enemy[j].isAlive = false;
                           				score += 30;
                           				if( rand() % 6 == 1 )
                           				    CreateItem(&item[j], enemy[j].posX, enemy[j].posY);
                           				CreateParticle(bubble[j], bubble_num, enemy[j].posX, enemy[j].posY);
                           				playSoundEffect( BOOM_SOUND, 0.9 );
                           			}
                           		}
                           	}
                   	  }
                     	   draw2DPicture( arm_equip_type, modelViewProjection);
                   }
              }

               for(int i = 0; i < 10; ++i) {
                   	for(int j = 0; j < bubble_num; ++j) {
       					if(bubble[i][j].isActive) {
       						modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
       						for(int k = 0; k < 16; ++k) {
       							if((k != 14))
       								modelViewMatrix.data[k] = 0.0f;
       							if(k % 5 == 0)
       								modelViewMatrix.data[k] = 1.0f;
       						}
       						SampleUtils::translatePoseMatrix(bubble[i][j].posX, bubble[i][j].posY, 0.0f, &modelViewMatrix.data[0]);
       						SampleUtils::scalePoseMatrix(bubble[i][j].size, bubble[i][j].size, 0.0, &modelViewMatrix.data[0]);
       						SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);

       						draw2DPicture( TEXTURE_BUBBLE, modelViewProjection);
       					}
                   	}
                   	 EvolveParticle(bubble[i], bubble_num, shootemup_dt);
              }

           	for(int i = 0; i < 10; ++i) {
           		if(item[i].isActive) {
           			modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
           			for(int j = 0; j < 16; ++j) {
           				if((j != 14))
           					modelViewMatrix.data[j] = 0.0f;
           				if(j % 5 == 0)
           					modelViewMatrix.data[j] = 1.0f;
           			}
           			SampleUtils::translatePoseMatrix(item[i].posX, item[i].posY, 0.0f, &modelViewMatrix.data[0]);
           			SampleUtils::scalePoseMatrix(45.0, 45.0, 0.0, &modelViewMatrix.data[0]);
           			SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);

           			createBoundingBox(&item[i].bb, planeVertices, NUM_PLANE_VERTEX);
           			calculateBoundingBox(&item[i].bb, modelViewMatrix);

           			if(BoundingBoxIntersect(cubebox, item[i].bb)) {
           				item[i].isActive = false;
           				if(item[i].type == 0) {

           				}
           				else if(item[i].type == 1) {

           				}
           				playSoundEffect( SMILE_SOUND, 0.8);
           				shootemup_prevTime_item = getCurrentTime();
           				bullet_flower_isActive = true;
           			}
           			draw2DPicture(TEXTURE_CRYSTAL_BLUE, modelViewProjection);
           			MoveItem(&item[i], shootemup_dt);
           		}
              }

              //display score
              loadIdentity(modelViewMatrix);
              SampleUtils::translatePoseMatrix( -0.82f, -0.55f, 2.0f, &modelViewMatrix.data[0]);
              SampleUtils::scalePoseMatrix(0.164, 0.059, 0.0, &modelViewMatrix.data[0]);
              SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
              draw2DPicture(TEXTURE_SCORE, modelViewProjection);
              NumberDisplay( score , 0.58, 0.55, modelViewMatrix, modelViewProjection);

              if( pet_shoot_HP == 0 ){
                 showMainButton();
                 main_menu = true;
                 prevTime_talk = getCurrentTime();
                 shootemup_start = false;
                 if ( score > top_score )
                	 top_score = score;
              }
              if( pet_shoot_HP >= 1 ){
            	 loadIdentity(modelViewMatrix);
                 SampleUtils::translatePoseMatrix( -0.9f, 0.5f, 2.0f, &modelViewMatrix.data[0]);
                 SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
                 SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
                 draw2DPicture(TEXTURE_HEART, modelViewProjection);
              }
              if( pet_shoot_HP >= 2 ){
            	  loadIdentity(modelViewMatrix);
                  SampleUtils::translatePoseMatrix( -0.69f, 0.5f, 2.0f, &modelViewMatrix.data[0]);
                  SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
                  SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
                  draw2DPicture(TEXTURE_HEART, modelViewProjection);
              }
              if( pet_shoot_HP >= 3 ){
            	  loadIdentity(modelViewMatrix);
                  SampleUtils::translatePoseMatrix( -0.48f, 0.5f, 2.0f, &modelViewMatrix.data[0]);
                  SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
                  SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
                  draw2DPicture(TEXTURE_HEART, modelViewProjection);
             }
             shootemup_prev_time = shootemup_cur_time;
        }

        //Beleaguered game
        glEnable(GL_DEPTH_TEST);
        static double zombie_prev_time;
        static double missile_prev_time;
        static double zombie_wave_prev_time;
        static float  game_wave_change_time;

        double zombie_cur_time = getCurrentTime();
        float zombie_dt = (float)(zombie_cur_time - zombie_prev_time);
        zombie_prev_time = zombie_cur_time;

        if(shotgun_init) {
          pet_zombie_HP = 3;
          missilecount = 0;
          shotgun_enable = true;
          zombie_wave = 0;
          shotgun_init = false;
          wave_interval = 5.0;
          zombie_wave_prev_time = getCurrentTime();
          game_wave_change_time = 0;
          for(int i = 0; i < 10; ++i) {
            missile[i].isActive = false;
          }
          for(int i = 0; i < ZOMBIECOUNT; i++){
        	zombie[i].isAlive = false;
          }
        }

	   if(shotgun_enable) {

		   double zombie_wave_cur_time = getCurrentTime();
	       float zombie_wave_dt = (float)(zombie_wave_cur_time - zombie_wave_prev_time);

	       if( wave_interval > 2.0){
	    	   if(game_wave_change_time > 10.0){
	    		   wave_interval -= 1.0;
	      	       game_wave_change_time = 0.0;
	    	   }
	       }

		   if( zombie_wave_dt > wave_interval  ) {
		 	   zombie_wave = (zombie_wave % 3) + 1; // wave: 1 ~ 3
		 	   zombie_new_wave = true;
		   	   zombie_wave_prev_time = zombie_wave_cur_time;

		       if(game_wave_change_time < 15.0)
		    	   game_wave_change_time += zombie_wave_dt;
		   }

		   if(zombie_new_wave){
	           for( int i=0; i<WAVEZOMBIES; i++ ){    // each wave adds 3 zombies
	        	 if(!zombie[i+(zombie_wave-1)*3].isAlive) {
	        		 float randX = (float)(rand() % 1000) - 500.0;
	        		 float randZ = (rand() % 2) ? sqrt(500 * 500 - randX * randX) : -sqrt(500 * 500 - randX * randX);
	        		 modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
	        		 zombie[i+(zombie_wave-1)*3].posX = randX;
	        		 zombie[i+(zombie_wave-1)*3].posZ = randZ;
	        	 	 float zombie_speed = sqrt(randX * randX + randZ * randZ);
	        	 	 zombie[i+(zombie_wave-1)*3].speedX = -randX * 50 / zombie_speed;
	        	 	 zombie[i+(zombie_wave-1)*3].speedZ = -randZ * 50 / zombie_speed;
	        	 	 zombie[i+(zombie_wave-1)*3].isAlive = true;
	        	 	zombie[i+(zombie_wave-1)*3].hp = 2;
	        	 	 zombie_new_wave = false;
	        	 }
	           }
		   }

		 for(int i = 0; i < ZOMBIECOUNT; ++i) {
			 if(zombie[i].isAlive) {
				 float zombie_speed = sqrt(zombie[i].posX * zombie[i].posX + zombie[i].posZ * zombie[i].posZ);
				 zombie[i].speedX = -zombie[i].posX * 50 / zombie_speed;
				 zombie[i].speedZ = -zombie[i].posZ * 50 / zombie_speed;

				 zombie[i].posX += zombie[i].speedX * zombie_dt;
				 zombie[i].posZ += zombie[i].speedZ * zombie_dt;

				 modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
				 SampleUtils::translatePoseMatrix(zombie[i].posX, 0.0, zombie[i].posZ, &modelViewMatrix.data[0]);
				 SampleUtils::scalePoseMatrix(50.0, 50.0, 60.0, &modelViewMatrix.data[0]);
				 SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
				 createBoundingBox(&zombie[i].bb, cubeVertices, NUM_CUBE_VERTEX);
				 calculateBoundingBox(&zombie[i].bb, modelViewMatrix);

				 if(BoundingBoxIntersect(zombie[i].bb, cubebox)) {
					 pet_zombie_HP -= 1;
					 zombie[i].isAlive = false;
					 //zombie[i].posX -= zombie[i].speedX * zombie_dt;
					 //zombie[i].posZ -= zombie[i].speedZ * zombie_dt;
					 if(pet_zombie_HP == 0){
						 isDie = true;
						 isHurt = false;
						 prevTime_die = getCurrentTime();
						 playSoundEffect( DIE_SOUND, 0.6 );
					 }
					 else{
						 isHurt = true;
						 prevTime_hurt = getCurrentTime();
						 playSoundEffect( HURT_SOUND, 0.8);
					 }
				 }

				/* static double prevTime_zombie_die;
				 if(zombie_die){
					 double curTime_zombie_die = getCurrentTime();
					 float zombie_die_dt = (float)(curTime_zombie_die - prevTime_zombie_die);
					 if( zombie_die_dt > 0.5){
						 zombie_die = false;
					 }
				 }*/

				 glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeVertices[0]);
				 glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeNormals[0]);
				 glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeTexCoords[0]);

				 glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ZOMBIE]->mTextureID);
				 glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&modelViewProjection.data[0]);
				 glDrawElements(GL_TRIANGLES, NUM_CUBE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &cubeIndices[0]);
			}
    	}

        	if(shotgun_isShot) {
        		modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
        		QCAR::Matrix44F inverseMV = SampleMath::Matrix44FInverse(modelViewMatrix);
        		QCAR::Matrix44F invTranspMV = SampleMath::Matrix44FTranspose(inverseMV);
        		missile[missilecount].posX = invTranspMV.data[12] + invTranspMV.data[8] * 100.0;
        		missile[missilecount].posY = invTranspMV.data[13] + invTranspMV.data[9] * 100.0;
        		missile[missilecount].posZ = invTranspMV.data[14] + invTranspMV.data[10] * 100.0;
        		missile[missilecount].speedX = invTranspMV.data[8] * 1250.0;
        		missile[missilecount].speedY = invTranspMV.data[9] * 1250.0;
        		missile[missilecount].speedZ = invTranspMV.data[10] * 1250.0;
        		missile[missilecount].isActive = true;
        		missilecount = (missilecount + 1) % 10;
        		missile_prev_time = getCurrentTime();
        		shotgun_isShot = false;
        		playSoundEffect( MISSILE_SOUND, 0.8);
        	}

        	double missile_cur_time = getCurrentTime();
        	float missile_dt = (float)(missile_cur_time - missile_prev_time);
        	for(int i = 0; i < 10; ++i) {
        		if(missile[i].isActive) {
        			missile[i].posX += missile_dt * missile[i].speedX * 1.2;
        			missile[i].posY += missile_dt * missile[i].speedY * 1.2;
        			missile[i].posZ += missile_dt * missile[i].speedZ * 1.2;

        			modelViewMatrix = QCAR::Tool::convertPose2GLMatrix(result->getPose());
					SampleUtils::translatePoseMatrix(missile[i].posX, missile[i].posY, missile[i].posZ, &modelViewMatrix.data[0]);
					//SampleUtils::scalePoseMatrix(5.0, 5.0, 5.0, &modelViewMatrix.data[0]);
					SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
					createBoundingBox(&missile[i].bb, ballVertices, NUM_BALL_VERTEX);
					calculateBoundingBox(&missile[i].bb, modelViewMatrix);

					for(int j = 0; j < ZOMBIECOUNT; ++j) {
						if(zombie[j].isAlive) {
							if(BoundingBoxIntersect(zombie[j].bb, missile[i].bb)) {
								missile[i].isActive = false;
								zombie[j].hp -= 1;
								if(zombie[j].hp == 0){
									zombie[j].isAlive = false;
									playSoundEffect( ZOMBIE_SOUND, 0.9 );
								}
								//zombie_die = true;
							   // prevTime_zombie_die = getCurrentTime();
							}
						}
					}

					glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &ballVertices[0]);
					glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &ballNormals[0]);
					glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &ballTexCoords[0]);

					glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_LIGHTBALL]->mTextureID);
					glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&modelViewProjection.data[0]);
					glDrawElements(GL_TRIANGLES, NUM_BALL_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &ballIndices[0]);
        		}
        	}

        	glDisable(GL_DEPTH_TEST);
			if( pet_zombie_HP == 0 ){
				shotgun_enable = false;
				showMainButton();
				main_menu = true;
				prevTime_talk = getCurrentTime();
				glDisable(GL_DEPTH_TEST);
				playSoundEffect( DIE_SOUND, 0.6 );
			}
			if( pet_zombie_HP >= 1 ){
			       loadIdentity(modelViewMatrix);
			       SampleUtils::translatePoseMatrix( -0.9f, -0.5f, 2.0f, &modelViewMatrix.data[0]);
			       SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
			       SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
			       draw2DPicture(TEXTURE_HEART, modelViewProjection);
			}
			if( pet_zombie_HP >= 2 ){
		     	  loadIdentity(modelViewMatrix);
			      SampleUtils::translatePoseMatrix( -0.69f, -0.5f, 2.0f, &modelViewMatrix.data[0]);
			      SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
			      SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
			      draw2DPicture(TEXTURE_HEART, modelViewProjection);
			}
			if( pet_zombie_HP >= 3 ){
			      loadIdentity(modelViewMatrix);
			      SampleUtils::translatePoseMatrix( -0.48f, -0.5f, 2.0f, &modelViewMatrix.data[0]);
			      SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
			      SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
			      draw2DPicture(TEXTURE_HEART, modelViewProjection);
			}
        	loadIdentity(modelViewMatrix);
            SampleUtils::translatePoseMatrix( 0.0f, 0.0f, 2.0f, &modelViewMatrix.data[0]);
            SampleUtils::scalePoseMatrix(0.1, 0.1, 0.0, &modelViewMatrix.data[0]);
        	SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &modelViewMatrix.data[0], &modelViewProjection.data[0]);
		    draw2DPicture(TEXTURE_TARGET, modelViewProjection);

        	missile_prev_time = missile_cur_time;
        }

        SampleUtils::checkGlError("MultiTargets renderFrame");
    }
    else if ( state.getNumTrackableResults() == 0 && !ShopActive ){
    	static double prevTime_message;
    	if( display_message ){
    			displayMessage("Please put the target into camera.");
    			display_message = false;
    			prevTime_message = getCurrentTime();
    	}

		double cur_message = getCurrentTime();
		float dt_message = (float)( cur_message - prevTime_message);
		if( dt_message > 8.0 ){
			display_message = true;
		}

    }

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glDisableVertexAttribArray(vertexHandle);
    glDisableVertexAttribArray(normalHandle);
    glDisableVertexAttribArray(textureCoordHandle);

    QCAR::Renderer::getInstance().end();
}


void
configureVideoBackground()
{
    // Get the default video mode:
    QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
    QCAR::VideoMode videoMode = cameraDevice.getVideoMode(QCAR::CameraDevice::MODE_DEFAULT);

    // Configure the video background
    QCAR::VideoBackgroundConfig config;
    config.mEnabled = true;
    config.mSynchronous = true;
    config.mPosition.data[0] = 0.0f;
    config.mPosition.data[1] = 0.0f;
    
    if (isActivityInPortraitMode)
    {
        //LOG("configureVideoBackground PORTRAIT");
        config.mSize.data[0] = videoMode.mHeight * (screenHeight / (float)videoMode.mWidth);
        config.mSize.data[1] = screenHeight;

        if(config.mSize.data[0] < screenWidth)
        {
            LOG("Correcting rendering background size to handle missmatch between screen and video aspect ratios.");
            config.mSize.data[0] = screenWidth;
            config.mSize.data[1] = screenWidth * (videoMode.mWidth / (float)videoMode.mHeight);
        }
    }
    else
    {
        //LOG("configureVideoBackground LANDSCAPE");
        config.mSize.data[0] = screenWidth;
        config.mSize.data[1] = videoMode.mHeight * (screenWidth / (float)videoMode.mWidth);

        if(config.mSize.data[1] < screenHeight)
        {
            LOG("Correcting rendering background size to handle missmatch between screen and video aspect ratios.");
            config.mSize.data[0] = screenHeight * (videoMode.mWidth / (float)videoMode.mHeight);
            config.mSize.data[1] = screenHeight;
        }
    }
    // Set the config:
    QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_initApplicationNative(JNIEnv* env, jobject obj, jint width, jint height)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_initApplicationNative");
    
    // Store screen dimensions
    screenWidth = width;
    screenHeight = height;
        
    // Handle to the activity class:
    //jclass
    activityClass = env->GetObjectClass(obj);

    jmethodID getMoneyDataID = env->GetMethodID(activityClass, "getMoneyData", "()I");
    jmethodID getScoreDataID = env->GetMethodID(activityClass, "getScoreData", "()I");
    jmethodID getBpDataID    = env->GetMethodID(activityClass, "getBpData", "()I");
    jmethodID getBearDataID  = env->GetMethodID(activityClass, "getBearData", "()Z");
    jmethodID getCatDataID   = env->GetMethodID(activityClass, "getCatData", "()Z");
    jmethodID getSkinDataID  = env->GetMethodID(activityClass, "getSkinData", "()I");
    jmethodID getBerryDataID  = env->GetMethodID(activityClass, "getBerryData", "()I");
    jmethodID getCheeseDataID = env->GetMethodID(activityClass, "getCheeseData", "()I");
    jmethodID getBullet1DataID   = env->GetMethodID(activityClass, "getBullet1Data", "()Z");
    jmethodID getBullet2DataID   = env->GetMethodID(activityClass, "getBullet2Data", "()Z");
    jmethodID getArmTypeDataID   = env->GetMethodID(activityClass, "getArmTypeData", "()I");

     total_money = env->CallIntMethod(obj, getMoneyDataID);
     top_score   = env->CallIntMethod(obj, getScoreDataID);
     pet_BP      = env->CallIntMethod(obj, getBpDataID);
     buy_bear    = env->CallBooleanMethod(obj, getBearDataID);
     buy_cat     = env->CallBooleanMethod(obj, getCatDataID);
     Skin_equip_normal = env->CallIntMethod(obj, getSkinDataID);
     berryHolding  = env->CallIntMethod(obj, getBerryDataID);
     cheeseHolding = env->CallIntMethod(obj, getCheeseDataID);
     buy_bullet1   = env->CallBooleanMethod(obj, getBullet1DataID);
     buy_bullet2   = env->CallBooleanMethod(obj, getBullet2DataID);
     arm_equip_type= env->CallIntMethod(obj, getArmTypeDataID);

    jmethodID getTextureCountMethodID = env->GetMethodID(activityClass, "getTextureCount", "()I");
    if (getTextureCountMethodID == 0)
    {
        LOG("Function getTextureCount() not found.");
        return;
    }

    textureCount = env->CallIntMethod(obj, getTextureCountMethodID);    
    if (!textureCount)
    {
        LOG("getTextureCount() returned zero.");
        return;
    }

    textures = new Texture*[textureCount];

    jmethodID getTextureMethodID = env->GetMethodID(activityClass, "getTexture", "(I)Lcom/qualcomm/QCARSamples/MultiTargets/Texture;");

    if (getTextureMethodID == 0)
    {
        LOG("Function getTexture() not found.");
        return;
    }

    // Register the textures
    for (int i = 0; i < textureCount; ++i)
    {

        jobject textureObject = env->CallObjectMethod(obj, getTextureMethodID, i); 
        if (textureObject == NULL)
        {
            LOG("GetTexture() returned zero pointer");
            return;
        }

        textures[i] = Texture::create(env, textureObject);
    }
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_deinitApplicationNative(JNIEnv* env, jobject obj)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_deinitApplicationNative");

    // Release texture resources
    if (textures != 0)
    {    
        for (int i = 0; i < textureCount; ++i)
        {
            delete textures[i];
            textures[i] = NULL;
        }
    
        delete[]textures;
        textures = NULL;
        
        textureCount = 0;
    }
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_startCamera(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_startCamera");
    
    // Select the camera to open, set this to QCAR::CameraDevice::CAMERA_FRONT 
    // to activate the front camera instead.
    QCAR::CameraDevice::CAMERA camera = QCAR::CameraDevice::CAMERA_DEFAULT;

    // Initialize the camera:
    if (!QCAR::CameraDevice::getInstance().init(camera))
        return;

    // Configure the video background
    configureVideoBackground();

    // Select the default mode:
    if (!QCAR::CameraDevice::getInstance().selectVideoMode(QCAR::CameraDevice::MODE_DEFAULT))
        return;

    // Start the camera:
    if (!QCAR::CameraDevice::getInstance().start())
        return;

    // Start the tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::Tracker* imageTracker = trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER);
    if(imageTracker != 0)
        imageTracker->start();
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_stopCamera(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_stopCamera");
    
    // Stop the tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::Tracker* imageTracker = trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER);
    if(imageTracker != 0)
        imageTracker->stop();
    
    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_setProjectionMatrix(JNIEnv *, jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_setProjectionMatrix");

    // Cache the projection matrix:
    const QCAR::CameraCalibration& cameraCalibration = QCAR::CameraDevice::getInstance().getCameraCalibration();
    projectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f, 2500.0f);
}

JNIEXPORT jboolean JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_autofocus(JNIEnv*, jobject)
{
    return QCAR::CameraDevice::getInstance().setFocusMode(QCAR::CameraDevice::FOCUS_MODE_TRIGGERAUTO) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_setFocusMode(JNIEnv*, jobject, jint mode)
{
    int qcarFocusMode;

    switch ((int)mode)
    {
        case 0:
            qcarFocusMode = QCAR::CameraDevice::FOCUS_MODE_NORMAL;
            break;
        
        case 1:
            qcarFocusMode = QCAR::CameraDevice::FOCUS_MODE_CONTINUOUSAUTO;
            break;
            
        case 2:
            qcarFocusMode = QCAR::CameraDevice::FOCUS_MODE_INFINITY;
            break;
            
        case 3:
            qcarFocusMode = QCAR::CameraDevice::FOCUS_MODE_MACRO;
            break;
    
        default:
            return JNI_FALSE;
    }
    
    return QCAR::CameraDevice::getInstance().setFocusMode(qcarFocusMode) ? JNI_TRUE : JNI_FALSE;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargetsRenderer_initRendering(JNIEnv* env, jobject obj)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargetsRenderer_initRendering");


    // Define clear color
    glClearColor(0.0f, 0.0f, 0.0f, QCAR::requiresAlpha() ? 0.0f : 1.0f);
    
    // Now generate the OpenGL texture objects and add settings
    for (int i = 0; i < textureCount; ++i)
    {
        glGenTextures(1, &(textures[i]->mTextureID));
        glBindTexture(GL_TEXTURE_2D, textures[i]->mTextureID);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[i]->mWidth, textures[i]->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) textures[i]->mData);
    }
  
    shaderProgramID     = SampleUtils::createProgramFromBuffer(cubeMeshVertexShader, cubeFragmentShader);

    vertexHandle        = glGetAttribLocation(shaderProgramID, "vertexPosition");
    normalHandle        = glGetAttribLocation(shaderProgramID, "vertexNormal");
    textureCoordHandle  = glGetAttribLocation(shaderProgramID, "vertexTexCoord");
    mvpMatrixHandle     = glGetUniformLocation(shaderProgramID, "modelViewProjectionMatrix");
    texSampler2DHandle  = glGetUniformLocation(shaderProgramID, "texSampler2D");

    // initialize timer
     prevTime_talk = getCurrentTime();
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargetsRenderer_updateRendering(JNIEnv* env, jobject obj, jint width, jint height)
{
    LOG("Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargetsRenderer_updateRendering");
    
    // Update screen dimensions
    screenWidth = width;
    screenHeight = height;

    // Reconfigure the video background
    configureVideoBackground();
}


QCAR::ImageTarget*
findImageTarget(const char* name)
{
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::ImageTracker* imageTracker = (QCAR::ImageTracker*)
                        trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER);

    if (imageTracker != 0)
    {
        for(int i=0; i<dataSet->getNumTrackables(); i++)
        {
            if(dataSet->getTrackable(i)->getType()==QCAR::Trackable::IMAGE_TARGET)
            {
                if(!strcmp(dataSet->getTrackable(i)->getName(),name))
                    return reinterpret_cast<QCAR::ImageTarget*>(dataSet->getTrackable(i));
            }
        }
    }
    return NULL;
}


void
initMIT()
{
    //
    // This function checks the current tracking setup for completeness. If
    // it finds that something is missing, then it creates it and configures it:
    // Any MultiTarget and Part elements missing from the config.xml file
    // will be created.
    //

    LOG("Beginning to check the tracking setup");

    // Configuration data - identical to what is in the config.xml file
    //
    // If you want to recreate the trackable assets using the on-line TMS server 
    // using the original images provided in the sample's media folder, use the
    // following trackable sizes on creation to get identical visual results:
    // create a cuboid with width = 90 ; height = 120 ; length = 60.
    
    const char* names[6]   = { "FlakesBox.Front", "FlakesBox.Back", "FlakesBox.Left", "FlakesBox.Right", "FlakesBox.Top", "FlakesBox.Bottom" };
    const float trans[3*6] = { 0.0f,  0.0f,  30.0f, 
                               0.0f,  0.0f, -30.0f,
                              -45.0f, 0.0f,  0.0f, 
                               45.0f, 0.0f,  0.0f,
                               0.0f,  60.0f, 0.0f,
                               0.0f, -60.0f, 0.0f };
    const float rots[4*6]  = { 1.0f, 0.0f, 0.0f,   0.0f,
                               0.0f, 1.0f, 0.0f, 180.0f,
                               0.0f, 1.0f, 0.0f, -90.0f,
                               0.0f, 1.0f, 0.0f,  90.0f,
                               1.0f, 0.0f, 0.0f, -90.0f,
                               1.0f, 0.0f, 0.0f,  90.0f };

    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::ImageTracker* imageTracker = (QCAR::ImageTracker*)
        trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER);

    if (imageTracker == 0 || dataSet == 0)
    {
        return;
    }

    // Go through all Trackables to find the MultiTarget instance
    //
    for(int i=0; i<dataSet->getNumTrackables(); i++)
    {
        if(dataSet->getTrackable(i)->getType()==QCAR::Trackable::MULTI_TARGET)
        {
            LOG("MultiTarget exists -> no need to create one");
            mit = reinterpret_cast<QCAR::MultiTarget*>(dataSet->getTrackable(i));
            break;
        }
    }

    // If no MultiTarget was found, then let's create one.
    if(mit==NULL)
    {
        LOG("No MultiTarget found -> creating one");
        mit = dataSet->createMultiTarget("FlakesBox");

        if(mit==NULL)
        {
            LOG("ERROR: Failed to create the MultiTarget - probably the Tracker is running");
            return;
        }
    }

    // Try to find each ImageTarget. If we find it, this actually means that it
    // is not part of the MultiTarget yet: ImageTargets that are part of a
    // MultiTarget don't show up in the list of Trackables.
    // Each ImageTarget that we found, is then made a part of the
    // MultiTarget and a correct pose (reflecting the pose of the
    // config.xml file) is set).
    // 
    int numAdded = 0;
    for(int i=0; i<6; i++)
    {
        if(QCAR::ImageTarget* it = findImageTarget(names[i]))
        {
            LOG("ImageTarget '%s' found -> adding it as to the MultiTarget",
                names[i]);

            int idx = mit->addPart(it);
            QCAR::Vec3F t(trans+i*3),a(rots+i*4);
            QCAR::Matrix34F mat;

            QCAR::Tool::setTranslation(mat, t);
            QCAR::Tool::setRotation(mat, a, rots[i*4+3]);
            mit->setPartOffset(idx, mat);
            numAdded++;
        }
    }

    LOG("Added %d ImageTarget(s) to the MultiTarget", numAdded);

    if(mit->getNumParts()!=6)
    {
        LOG("ERROR: The MultiTarget should have 6 parts, but it reports %d parts",
            mit->getNumParts());
    }

    LOG("Finished checking the tracking setup");
}


double
getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double t = tv.tv_sec + tv.tv_usec/1000000.0;
    return t;
}

void NumberDisplay(int count, float x_pos, float y_pos, QCAR::Matrix44F& ModelMatrix, QCAR::Matrix44F& ProjectionMatrix)
{

	int num_digit = 0;
	int digits[30];
	int tmp_score = count;
	while(tmp_score > 0){
	     digits[num_digit] =  tmp_score % 10;
	     tmp_score = tmp_score / 10;
	     //__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "%d", tmp_score);
	     num_digit++;
	}

	if( count == 0 ){  // initial score = 0
	     loadIdentity(ModelMatrix);
	     SampleUtils::translatePoseMatrix( -x_pos, -y_pos, 2.0f, &ModelMatrix.data[0]);
	     SampleUtils::scalePoseMatrix(0.04, 0.04, 0.0, &ModelMatrix.data[0]);
	     SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &ModelMatrix.data[0], &ProjectionMatrix.data[0]);
	     draw2DPicture( Texture_num[0], ProjectionMatrix);
	 }
	 else{
	     for(int i=0; i<num_digit; i++){
	         // display from high digit to low digit
	         loadIdentity(ModelMatrix);
	         SampleUtils::translatePoseMatrix( (-x_pos + 0.1*i), -y_pos, 2.0f, &ModelMatrix.data[0]);
	         SampleUtils::scalePoseMatrix(0.04, 0.04, 0.0, &ModelMatrix.data[0]);
	         SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &ModelMatrix.data[0], &ProjectionMatrix.data[0]);
	         draw2DPicture( Texture_num[ digits[num_digit-1-i] ], ProjectionMatrix);
	     }
	 }
}

void CreateParticle(PARTICLE *particle, int num_particle, float explodeX, float explodeY)
{
	for(int i = 0; i < num_particle; ++i) {
		particle[i].lifetime = 0.3;
		particle[i].posX = explodeX;
		particle[i].posY = explodeY;
		particle[i].speedX = (float)(rand() % 500) - 250.0;
		particle[i].speedY = 100.0 - (float)(rand() % 400);
		particle[i].size = (float)(rand() % 20) + 10.0;
		particle[i].isActive = true;
	}
}


void EvolveParticle(PARTICLE *particle, int num_particle, float dt)
{
	for(int i = 0; i < num_particle; ++i) {
		if(particle[i].isActive) {
			particle[i].lifetime -= dt;
			particle[i].posX += particle[i].speedX*dt;
			particle[i].posY += particle[i].speedY*dt;
			particle[i].speedY -= 200.0 * dt;
			if(particle[i].lifetime < 0.0)
				particle[i].isActive = false;
		}
	}
}

void CreateItem(ITEM *item, float startX, float startY)
{
	item->posX = startX;
	item->posY = startY;
	item->speedX = 0.0;
	item->speedY = 100.0;
	item->type = rand() % 2;
	item->isActive = true;
}

void MoveItem(ITEM *item, float dt)
{
	item->posY += item->speedY * dt;
	item->speedY += 10.0 * dt;
}

void
loadIdentity(QCAR::Matrix44F& modelViewMatrix)
{
	for(int i=0; i<16; i++){
		modelViewMatrix.data[i] = 0;
		if( i % 5 == 0)
		   modelViewMatrix.data[i] = 1;
	}
}

void
draw2DPicture(int textureID, QCAR::Matrix44F& ProjectionMatrix)
{
	glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &planeVertices[0]);
	glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &planeNormals[0]);
    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &planeTexCoords[0]);

	glBindTexture(GL_TEXTURE_2D, textures[textureID]->mTextureID);
	glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&ProjectionMatrix.data[0]);
	glDrawElements(GL_TRIANGLES, NUM_PLANE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &planeIndices[0]);
}

void
createBoundingBox(BOUNDINGBOX *b, float *o, int indices)
{
	BOUNDINGBOX newbox;
	newbox.xmin = o[0];
	newbox.xmax = o[0];
	newbox.ymin = o[1];
	newbox.ymax = o[1];
	newbox.zmin = o[2];
	newbox.zmax = o[2];

    for(int i=1; i < indices; ++i)
    {
    	if( o[i*3] < newbox.xmin)
    		newbox.xmin = o[i*3];
    	if( o[i*3] > newbox.xmax)
    		newbox.xmax = o[i*3];
    	if( o[i*3+1] < newbox.ymin)
    		newbox.ymin = o[i*3+1];
    	if( o[i*3+1] > newbox.ymax)
    		newbox.ymax = o[i*3+1];
    	if( o[i*3+2] < newbox.zmin)
    		newbox.zmin = o[i*3+2];
    	if( o[i*3+2] > newbox.zmax)
    		newbox.zmax = o[i*3+2];
    }

    *b = newbox;
}

void
calculateBoundingBox(BOUNDINGBOX *b, QCAR::Matrix44F& m)
{
	BOUNDINGBOX newbox;
	QCAR::Vec3F v;
    QCAR::Vec3F r;
    float w;

	v.data[0] = b->xmin;
	v.data[1] = b->ymin;
	v.data[2] = b->zmin;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;


	newbox.xmin = r.data[0];
	newbox.xmax = r.data[0];
	newbox.ymin = r.data[1];
	newbox.ymax = r.data[1];
	newbox.zmin = r.data[2];
	newbox.zmax = r.data[2];

	v.data[0] = b->xmax;
	v.data[1] = b->ymin;
	v.data[2] = b->zmin;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;

	if(r.data[0] < newbox.xmin)
		newbox.xmin = r.data[0];
	if(r.data[0] > newbox.xmax)
		newbox.xmax = r.data[0];
	if(r.data[1] < newbox.ymin)
		newbox.ymin = r.data[1];
	if(r.data[1] > newbox.ymax)
		newbox.ymax = r.data[1];
	if(r.data[2] < newbox.zmin)
		newbox.zmin = r.data[2];
	if(r.data[2] > newbox.zmax)
		newbox.zmax = r.data[2];

	v.data[0] = b->xmax;
	v.data[1] = b->ymax;
	v.data[2] = b->zmin;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;

	if(r.data[0] < newbox.xmin)
		newbox.xmin = r.data[0];
	if(r.data[0] > newbox.xmax)
		newbox.xmax = r.data[0];
	if(r.data[1] < newbox.ymin)
		newbox.ymin = r.data[1];
	if(r.data[1] > newbox.ymax)
		newbox.ymax = r.data[1];
	if(r.data[2] < newbox.zmin)
		newbox.zmin = r.data[2];
	if(r.data[2] > newbox.zmax)
		newbox.zmax = r.data[2];

	v.data[0] = b->xmin;
	v.data[1] = b->ymax;
	v.data[2] = b->zmin;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;

	if(r.data[0] < newbox.xmin)
		newbox.xmin = r.data[0];
	if(r.data[0] > newbox.xmax)
		newbox.xmax = r.data[0];
	if(r.data[1] < newbox.ymin)
		newbox.ymin = r.data[1];
	if(r.data[1] > newbox.ymax)
		newbox.ymax = r.data[1];
	if(r.data[2] < newbox.zmin)
		newbox.zmin = r.data[2];
	if(r.data[2] > newbox.zmax)
		newbox.zmax = r.data[2];

	v.data[0] = b->xmin;
	v.data[1] = b->ymax;
	v.data[2] = b->zmax;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;

	if(r.data[0] < newbox.xmin)
		newbox.xmin = r.data[0];
	if(r.data[0] > newbox.xmax)
		newbox.xmax = r.data[0];
	if(r.data[1] < newbox.ymin)
		newbox.ymin = r.data[1];
	if(r.data[1] > newbox.ymax)
		newbox.ymax = r.data[1];
	if(r.data[2] < newbox.zmin)
		newbox.zmin = r.data[2];
	if(r.data[2] > newbox.zmax)
		newbox.zmax = r.data[2];

	v.data[0] = b->xmin;
	v.data[1] = b->ymin;
	v.data[2] = b->zmax;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;

	if(r.data[0] < newbox.xmin)
		newbox.xmin = r.data[0];
	if(r.data[0] > newbox.xmax)
		newbox.xmax = r.data[0];
	if(r.data[1] < newbox.ymin)
		newbox.ymin = r.data[1];
	if(r.data[1] > newbox.ymax)
		newbox.ymax = r.data[1];
	if(r.data[2] < newbox.zmin)
		newbox.zmin = r.data[2];
	if(r.data[2] > newbox.zmax)
		newbox.zmax = r.data[2];

	v.data[0] = b->xmax;
	v.data[1] = b->ymin;
	v.data[2] = b->zmax;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;

	if(r.data[0] < newbox.xmin)
		newbox.xmin = r.data[0];
	if(r.data[0] > newbox.xmax)
		newbox.xmax = r.data[0];
	if(r.data[1] < newbox.ymin)
		newbox.ymin = r.data[1];
	if(r.data[1] > newbox.ymax)
		newbox.ymax = r.data[1];
	if(r.data[2] < newbox.zmin)
		newbox.zmin = r.data[2];
	if(r.data[2] > newbox.zmax)
		newbox.zmax = r.data[2];

	v.data[0] = b->xmax;
	v.data[1] = b->ymax;
	v.data[2] = b->zmax;

	w = m.data[3] + m.data[7] + m.data[11] + m.data[15];
    r.data[0] = (m.data[0] * v.data[0] + m.data[4] * v.data[1] + m.data[8] * v.data[2] +  m.data[12]) / w;
    r.data[1] = (m.data[1] * v.data[0] + m.data[5] * v.data[1] + m.data[9] * v.data[2] +  m.data[13]) / w;
    r.data[2] = (m.data[2] * v.data[0] + m.data[6] * v.data[1] + m.data[10] * v.data[2]  +  m.data[14]) / w;

	if(r.data[0] < newbox.xmin)
		newbox.xmin = r.data[0];
	if(r.data[0] > newbox.xmax)
		newbox.xmax = r.data[0];
	if(r.data[1] < newbox.ymin)
		newbox.ymin = r.data[1];
	if(r.data[1] > newbox.ymax)
		newbox.ymax = r.data[1];
	if(r.data[2] < newbox.zmin)
		newbox.zmin = r.data[2];
	if(r.data[2] > newbox.zmax)
		newbox.zmax = r.data[2];

	*b = newbox;
}

bool
insideBoundingBox(BOUNDINGBOX b, float x, float y, float z)
{
	if(x <= b.xmax && x >= b.xmin && y <= b.ymax && y >= b.ymin && z <= b.zmax && z >= b.zmin)
		return true;
	else
		return false;
}


bool
BoundingBoxIntersect(BOUNDINGBOX b1, BOUNDINGBOX b2)
{
	float center1x, center1y, center1z;
	float center2x, center2y, center2z;
	float edge1x, edge1y, edge1z;
	float edge2x, edge2y, edge2z;
	float distx, disty, distz;

	edge1x = (b1.xmax - b1.xmin) / 2;
	edge1y = (b1.ymax - b1.ymin) / 2;
	edge1z = (b1.zmax - b1.zmin) / 2;

	edge2x = (b2.xmax - b2.xmin) / 2;
	edge2y = (b2.ymax - b2.ymin) / 2;
	edge2z = (b2.zmax - b2.zmin) / 2;

	center1x = b1.xmin + edge1x;
	center1y = b1.ymin + edge1y;
	center1z = b1.zmin + edge1z;

	center2x = b2.xmin + edge2x;
	center2y = b2.ymin + edge2y;
	center2z = b2.zmin + edge2z;

	distx = (center1x > center2x) ? (center1x - center2x) : (center2x - center1x);
	disty = (center1y > center2y) ? (center1y - center2y) : (center2y - center1y);
	distz = (center1z > center2z) ? (center1z - center2z) : (center2z - center1z);

	if((distx <= edge1x + edge2x) && (disty <= edge1y + edge2y) && (distz <= edge1z + edge2z))
		return true;

	return false;
}

#ifdef __cplusplus
}
#endif
