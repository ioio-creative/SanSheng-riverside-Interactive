#pragma once
#include "ofMain.h"

/* ======================================================
//Compiler Flags
======================================================*/
//Use this flag to toggle window sizes for different usage
//#define IOIOTEST
//#define USE_TCP_COMMUNICATION
#define EXHIBITION
#define LANDSCAPE_MODE

/* ======================================================
//Includes
======================================================*/
#include "ofxCv.h"
#include "ofxJSON.h"
#include "VideoPlayerManager.h"
#include "ParticleVisualsManager.h"
#ifdef USE_TCP_COMMUNICATION
#include "TcpClientManager.h"
#endif
#include "ofxKinectForWindows2.h"
#include "ofxGui.h"
#include "ofxSerial.h"

#include "KinectManager.h"
#include "KinectToFloorScreenMapper.h"


/* ======================================================
//Settings
======================================================*/
#define VIDEO_FLOOR_TRIGGER_DELAY 375 //millis
#define VIDEO_PANEL_TRIGGER_DELAY 375 //millis

#define TARGET_FRAMERATE 25
//Serial
#define BAUD 115200
//Kinect sources dimensions
#define DEPTH_WIDTH 512
#define DEPTH_HEIGHT 424
#define DEPTH_SIZE DEPTH_WIDTH * DEPTH_HEIGHT

#define COLOR_WIDTH 1920
#define COLOR_HEIGHT 1080

#define MAX_PLAYERS 6

#ifdef EXHIBITION
#define CANVAS_WIDTH 1165
#define CANVAS_HEIGHT 3828
#define KINECTAREA_WIDTH CANVAS_WIDTH
#define KINECTAREA_HEIGHT 1548
#else
#define CANVAS_WIDTH 1200/3
#define CANVAS_HEIGHT 3840/3
#define KINECTAREA_WIDTH CANVAS_WIDTH
#define KINECTAREA_HEIGHT 1548/3
#endif

#ifdef IOIOTEST
#define CANVAS_WIDTH 1080
#define CANVAS_HEIGHT 1920
#define KINECTAREA_WIDTH CANVAS_WIDTH
#define KINECTAREA_HEIGHT CANVAS_HEIGHT
#endif



class SerialMessage
{
public:
	SerialMessage() : fade(0)
	{
	}

	SerialMessage(const std::string& _message,
		const std::string& _exception,
		int _fade) :
		message(_message),
		exception(_exception),
		fade(_fade)
	{
	}

	std::string message;
	std::string exception;
	int fade;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyReleased(int key);

		//unused
		void keyPressed(int key) {};
		void mouseMoved(int x, int y) {};
		void mouseDragged(int x, int y, int button) {};
		void mousePressed(int x, int y, int button) {};
		void mouseReleased(int x, int y, int button) {};
		void mouseEntered(int x, int y) {};
		void mouseExited(int x, int y) {};
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo) {};
		void gotMessage(ofMessage msg) {};

		//basic variables
		bool debugMode;
		int w, h;

		//kinect
		//ofxKFW2::Device kinect;
		//ICoordinateMapper* coordinateMapper;
		KinectManager* SanShengKinectManager = new KinectManager(int(CANVAS_WIDTH), int(CANVAS_HEIGHT / 3), int(MAX_PLAYERS));


		//float tiltAngle;
		//float rollAngle;
		//Vector4 floorPlane;
		//glm::mat4 floorTransform;

		//vector<bool> bodyIdxTracked;
		//vector<glm::vec3> bodyPositions;
		//vector<cv::Point2f> bodyPosOnFloor;
		//vector<cv::Point2f> bodyPosOnScreen;

		//ofTexture colorTex;
		//int numBodiesTracked;
		//bool bHaveAllStreams;

		//void setupKinect2();
		//void updateKinect2();
		//void drawKinectFbo();

		//------------------------------------- Kinect Mapping -------------------------------------
		KinectToFloorScreenMapper KinectMapper = KinectToFloorScreenMapper(int(KINECTAREA_WIDTH), int(KINECTAREA_HEIGHT));

		ofxPanel calibrationGui;

		ofParameterGroup bodyPosGuiGroup;
		ofxLabel selectedBodyLabel;
		ofParameter<int> refBodyIdx;
		ofParameter<string> bodyPosInspect[MAX_PLAYERS];
		ofParameter<bool> refBodyIdxFlags[MAX_PLAYERS];

		vector<ofVec2f> bodyPos;

		void refBodyIdxChanged(int& idx);


		bool calibrationMode = false;

		void setupCalibrationGui();
		void updateGuiInspectorValues();

		//fbo CG / video
		ofFbo CGFbo;
		//ofFbo KinectVisionFbo;
		//ofEasyCam kinect3DCam;


		//Settings
		ofxJSONElement settings;
		string dataPath;

		void saveSettings();
		void loadSettings();

		//------------------------------------- VideoPlayerManager -------------------------------------
		VideoPlayerManager VideoPlayerManager;
		bool drawVideoPlayerManager;

		vector<bool> isTriggerScene;
		vector<float> triggerSceneTime;
		int num_of_trigger_scene;

		void resetScene();

		//------------------------------------- Particle Visuals Manager-------------------------------------
		ParticleVisualsManager ParticleVisualsManager;
		bool drawParticleVisualsManager;

#ifdef USE_TCP_COMMUNICATION
		//------------------------------------- TCP Client Manager-------------------------------------
		TcpClientManager TcpClientManager;
#endif

		//------------------------------------- Serial ----------------------------------------------------

		void serialSetup();
		void serialDraw();

		string receivedString;

		ofxIO::BufferedSerialDevice arduino;

		std::vector<SerialMessage> serialMessages;

		bool isCommandDelay;
		void sendCommand(string s);

		void onSerialBuffer(const ofxIO::SerialBufferEventArgs& args);
		void onSerialError(const ofxIO::SerialBufferErrorEventArgs& args);

		//FROM Control Room
		string serialReadCtrlrm();
		string ctrlrmReceivedString;


#ifdef LANDSCAPE_MODE
		ofFbo landscapeFbo;
#endif
		void drawAll();

		void debugDraw();
};


/* ======================================================
 //TODO
 ======================================================*/

 /* ======================================================
  //Known Issue
  ======================================================*/
