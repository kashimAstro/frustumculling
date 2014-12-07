#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "ofxAssimpModelLoader.h"

class xFrustum : public ofBaseApp{
	public:

	bool frustum(GLfloat MVPMatrix[16], GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat radius) {
		enum term { A = 0, B, C, D };

 		GLfloat leftPlane[4];
		leftPlane[A] = MVPMatrix[3]  + MVPMatrix[0];
		leftPlane[B] = MVPMatrix[7]  + MVPMatrix[4];
		leftPlane[C] = MVPMatrix[11] + MVPMatrix[8];
		leftPlane[D] = MVPMatrix[15] + MVPMatrix[12];
 
		GLfloat length = sqrtf(leftPlane[A] * leftPlane[A] + leftPlane[B] * leftPlane[B] + leftPlane[C] * leftPlane[C]);
		leftPlane[A] /= length;
		leftPlane[B] /= length;
		leftPlane[C] /= length;
		leftPlane[D] /= length;
 
		GLfloat distance = leftPlane[A] * xPos + leftPlane[B] * yPos + leftPlane[C] * zPos + leftPlane[D];
		if (distance <= -radius) {
			return false; 
		}
		GLfloat rightPlane[4];
		rightPlane[A] = MVPMatrix[3]  - MVPMatrix[0];
		rightPlane[B] = MVPMatrix[7]  - MVPMatrix[4];
		rightPlane[C] = MVPMatrix[11] - MVPMatrix[8];
		rightPlane[D] = MVPMatrix[15] - MVPMatrix[12];
		length = sqrtf(rightPlane[A] * rightPlane[A] + rightPlane[B] * rightPlane[B] + rightPlane[C] * rightPlane[C]);
		rightPlane[A] /= length;
		rightPlane[B] /= length;
		rightPlane[C] /= length;
		rightPlane[D] /= length;
 		distance = rightPlane[A] * xPos + rightPlane[B] * yPos + rightPlane[C] * zPos + rightPlane[D];
		if (distance <= -radius) {
			return false; 
		}
		GLfloat bottomPlane[4];
		bottomPlane[A] = MVPMatrix[3]  + MVPMatrix[1];
		bottomPlane[B] = MVPMatrix[7]  + MVPMatrix[5];
		bottomPlane[C] = MVPMatrix[11] + MVPMatrix[9];
		bottomPlane[D] = MVPMatrix[15] + MVPMatrix[13];
 
		length = sqrtf(bottomPlane[A] * bottomPlane[A] + bottomPlane[B] * bottomPlane[B] + bottomPlane[C] * bottomPlane[C]);
		bottomPlane[A] /= length;
		bottomPlane[B] /= length;
		bottomPlane[C] /= length;
		bottomPlane[D] /= length;
 
		distance = bottomPlane[A] * xPos + bottomPlane[B] * yPos + bottomPlane[C] * zPos + bottomPlane[D];
		if (distance <= -radius){
			return false;
		}
		GLfloat topPlane[4];
		topPlane[A] = MVPMatrix[3]  - MVPMatrix[1];
		topPlane[B] = MVPMatrix[7]  - MVPMatrix[5];
		topPlane[C] = MVPMatrix[11] - MVPMatrix[9];
		topPlane[D] = MVPMatrix[15] - MVPMatrix[13];
		length = sqrtf(topPlane[A] * topPlane[A] + topPlane[B] * topPlane[B] + topPlane[C] * topPlane[C]);
		topPlane[A] /= length;
		topPlane[B] /= length;
		topPlane[C] /= length;
		topPlane[D] /= length;
 
		distance = topPlane[A] * xPos + topPlane[B] * yPos + topPlane[C] * zPos + topPlane[D];
		if (distance <= -radius) {
			return false;
		}
		GLfloat nearPlane[4];
		nearPlane[A] = MVPMatrix[3]  + MVPMatrix[2];
		nearPlane[B] = MVPMatrix[7]  + MVPMatrix[6];
		nearPlane[C] = MVPMatrix[11] + MVPMatrix[10];
		nearPlane[D] = MVPMatrix[15] + MVPMatrix[14];
		length = sqrtf(nearPlane[A] * nearPlane[A] + nearPlane[B] * nearPlane[B] + nearPlane[C] * nearPlane[C]);
		nearPlane[A] /= length;
		nearPlane[B] /= length;
		nearPlane[C] /= length;
		nearPlane[D] /= length;
		
		distance = nearPlane[A] * xPos + nearPlane[B] * yPos + nearPlane[C] * zPos + nearPlane[D];
		if (distance <= -radius) {
			return false; 
		}
		GLfloat farPlane[4];
		farPlane[A] = MVPMatrix[3]  - MVPMatrix[2];
		farPlane[B] = MVPMatrix[7]  - MVPMatrix[6];
		farPlane[C] = MVPMatrix[11] - MVPMatrix[10];
		farPlane[D] = MVPMatrix[15] - MVPMatrix[14];
		length = sqrtf(farPlane[A] * farPlane[A] + farPlane[B] * farPlane[B] + farPlane[C] * farPlane[C]);
		farPlane[A] /= length;
		farPlane[B] /= length;
		farPlane[C] /= length;
		farPlane[D] /= length;
		distance = farPlane[A] * xPos + farPlane[B] * yPos + farPlane[C] * zPos + farPlane[D];
		if (distance <= -radius) {
			return false;
		}
		return true;
	}

	ofEasyCam cam;
	ofLight light;
	ofxAssimpModelLoader model;

	void setup(){
	    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            glEnable(GL_DEPTH_TEST);
            ofEnableLighting();
            glShadeModel(GL_SMOOTH);
            light.enable();
            light.setSpotlight();
            ofEnableSeparateSpecularLight();
	    model.loadModel("avatar.dae",true);
	}

	void update(){
		ofSetWindowTitle(ofToString(ofGetFrameRate()));
	}

	void draw(){
		ofBackgroundGradient(200,0);
		cam.begin();

		ofMatrix4x4 mvp = cam.getModelViewProjectionMatrix();

		ofVec4f v1 = mvp.getRowAsVec4f(0);
		ofVec4f v2 = mvp.getRowAsVec4f(1);
		ofVec4f v3 = mvp.getRowAsVec4f(2);
		ofVec4f v4 = mvp.getRowAsVec4f(3);

		GLfloat m[16];
		m[0]=v1[0];
		m[1]=v1[1];
		m[2]=v1[2];
		m[3]=v1[3];

		m[4]=v2[0];
		m[5]=v2[1];
		m[6]=v2[2];
		m[7]=v2[3];

		m[8]=v3[0];
		m[9]=v3[1];
		m[10]=v3[2];
		m[11]=v3[3];

		m[12]=v4[0];
		m[13]=v4[1];
		m[14]=v4[2];
		m[15]=v4[3];
		
		bool view1 = frustum( m, 200, 0, 0, 20 );
		if( view1 ) {
			ofDrawSphere( 200, 0, 0, 20 );
		}

		bool view2 = frustum( m, 200, 200, 0, 20 );
		if( view2 ) {
			ofDrawBox( 200, 200, 0, 20 );
		}

		bool view3 = frustum( m, -200, 200, 0, 20 );
		if( view3 ) {
			ofDrawCone( -200, 200, 0, 20, 100 );
		}

		bool view4 = frustum( m, -200, 0, 200, 10 );
		if( view4 ) {
			model.setPosition( -200, 0, 200 );
			model.setScale(0.4,0.4,0.4);
			model.drawFaces();
		}

		cam.end();

		ofDrawBitmapStringHighlight( "Sphere:: "+ ofToString(view1),10,20);
		ofDrawBitmapStringHighlight( "Box:: "+    ofToString(view2),10,40);
		ofDrawBitmapStringHighlight( "Cone:: "+   ofToString(view3),10,60);
		ofDrawBitmapStringHighlight( "Collada:: "+ofToString(view4),10,80);
	}
	
	void keyPressed(int key){
	        
	}
};

int main( ){
    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
    ofRunApp( new xFrustum());
}
