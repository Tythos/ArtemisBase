/**
 * ArtemisBase.hpp
 */

#pragma once

#define _USE_MATH_DEFINES

#include <ctime>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <gl/glew.h>
#include <gl/GLU.h>
#include <gl/glu.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "ArtemisUtility.hpp"
#include "KirkMath.hpp"

namespace ArtemisBase {
    // --- PROTOTYPES --- //
    class App;
    class Camera;
    class Color;
    class Console;
    class Cursor;
    class Event;
    class EventList;
    class Graphics;
    class Keyboard;
    class Light;
    class Mesh;
    class Model;
    class Mouse;
    class Object;
    class Panel;
    class Skybox;
    class Soundboard;
    class Stopwatch;
    class TexCoord;
    class Texture;
    class Typewriter;
    class Vertex;

    // --- ENUMERATIONS --- //
    enum Alignment {
        ALIGN_NEGATIVE,
        ALIGN_MIDDLE,
        ALIGN_POSITIVE
    };

    enum ScreenUnit {
        UNIT_PIX,
        UNIT_PCT
    };

    enum MouseState {
        NO_BUTTONS,
        LEFT_BUTTON,
        RIGHT_BUTTON,
        BOTH_BUTTONS
    };

    enum ConsoleState {
        CS_UP,
        CS_DOWN,
        CS_MOVING_UP,
        CS_MOVING_DOWN
    };

    enum AppState {
        ASTATE_GLOBAL,
        ASTATE_MENU,
        ASTATE_INGAME,
        ASTATE_CINEMATIC
    };

    enum KeyState {
        AKEY_NONE,
        AKEY_NUM,
        AKEY_CAPS,
        AKEY_CTRL,
        AKEY_SHIFT,
        AKEY_ALT,
        AKEY_COMMAND,
        AKEY_WINDOWS
    };

    // --- DATA STRUCTURES --- //
    struct ConsoleLine {
        ArtemisUtility::String contents;
        int ttl;
        ConsoleLine * next;

        ConsoleLine() {
            contents = "";
            next = NULL;
        }

        ConsoleLine(ArtemisUtility::String stuff) {
            contents = stuff;
            next = NULL;
        }

        ~ConsoleLine() {
            if (next != NULL) {
                delete next;
                next = NULL;
            }
        }

        int numLines() {
            if (next == NULL) { return 1; }
            else { return next->numLines() + 1; }
        }

        ConsoleLine* get(int n) {
            if (n < 0) {
                // Negative index; return this
                return this;
            } else if (next == NULL && n > 0) {
                // Reached end; return last
                return this;
            } else if (n == 0) {
                // Reached desired location; return
                return this;
            } else {
                // Not there yet; increment
                return next->get(n-1);
            }
        }
    };

    struct ScreenDimension {
        float value;
        Alignment align;
        ScreenUnit unit;

        ScreenDimension() {
            value = 0.0f;
            align = ALIGN_NEGATIVE;
            unit = UNIT_PIX;
        }

        float toPct(float size) {
            if (unit == UNIT_PIX) {
                return value / size;
            } else {
                return value;
            }
        }

        float toPix(float size) {
            if (unit == UNIT_PIX) {
                return value;
            } else {
                return value * size;
            }
        }

        float toPct(int size) {
            float s = (float)(size);
            return toPct(s);
        }

        float toPix(int size) {
            float s = (float)(size);
            return toPix(s);
        }
    };

    // --- CLASSES --- //
    class App {
    private:
    protected:
        Panel* panels;
        Object* origin;
        Light* lights;
        KirkMath::Quat* globalAmbient;
        std::ofstream debugFile;
    public:
        // Data
        Graphics* hGraphics;
        Stopwatch* hStopwatch;
        Keyboard* hKeyboard;
        Mouse* hMouse;
        AppState currState;
        EventList* gameEvents;
        Camera* camera;
        Console* hConsole;
        Cursor* hCursor;
        Soundboard* hSoundboard;
        bool isDebugToFile;
        bool isDebugToConsole;
        bool isLooping;
        bool (*externalRender)(void);
        
        // Structors
        App();
        ~App();
        
        // Functions
        void initialize(int height, int width);
        void execute();
        void terminate();
        void mainLoop();
        void update();
        void render();
        void debug(ArtemisUtility::String msg);
        void fail(ArtemisUtility::String msg);

        // Origin management
        void setOriginVisibility(bool isVisible);

        // List management
        void addPanel(Panel* p);
        void addObject(Object* o);
        void addLight(Light* l);
        
        // Global settings
        void setGlobalAmbient(float r, float g, float b);
    };

    class Camera {
    private:
        KirkMath::Quat* position;
        KirkMath::Quat* target;
        KirkMath::Quat* up;
        float fieldAngle;
        float aspectRatio;
        float nearClip;
        float farClip;
        float singularityTolerance;
    protected:
    public:
        Camera();
        ~Camera();
        Skybox* skybox;
        
        // Set accessors
        void setPosition(float x, float y, float z);
        void setTarget(float x, float y, float z);
        void setUp(float x, float y, float z);
        void setRight(float x, float y, float z);
        void setFieldAngle(float v) { fieldAngle = v; }
        void setAspectRatio(float v) { aspectRatio = v; }
        void setNearClip(float v) { nearClip = v; }
        void setFarClip(float v);

        // Camera accessors
        float getFieldAngle() { return fieldAngle; }
        float getAspectRatio() { return aspectRatio; }
        float getNearClip() { return nearClip; }
        float getFarClip() { return farClip; }
        
        // Spacial accessors
        KirkMath::Quat* getPosition() { return position; }
        KirkMath::Quat* getTarget() { return target; }
        KirkMath::Quat* getUp() { return up; }
        
        void applyCamera();
        void print();

        // Skybox (background) settings
        void setSkyboxTexture(ArtemisUtility::String filename);
        void setSkyboxTexture(SDL_Surface * surf);
        void setSkyboxResolution(int n);
        void renderSkybox();

        // Movement functions
        void rotateFocus(float dTht, float dPhi);
        void rotateCenter(float dTht, float dPhi);
        void pan(float dx, float dy, float dz);
        void focus(float x, float y, float z);
        void zoomFocus(float dz);
    };
    
    class Color {
    private:
    protected:
    public:
        float r;
        float g;
        float b;
        float a;
        
        Color();
        Color(float fr, float fg, float fb, float fa);
        void set(float fr, float fg, float fb, float fa);
        void setAll();
        void setColor();
        void setDiffuseMat();
        void setAmbientMat();
    };

    class Event {
    private:
    protected:
    public:
        AppState eventState;
        bool (*trigger)(void);
        void (*target)(void);
        Event();
        ~Event();
    };

    class EventList {
    private:
        Event* thisEvent;
        EventList* nextNode;
    protected:
    public:
        EventList();
        ~EventList(); // NOTE: When a list is deleted, elements are also freed.
        
        // NOTE: All functions assume that they are being called for the head node.
        int listLength();
        int listLength(AppState myState);
        Event* getElement(int n);
        Event* createElement();
        void createElement(AppState myState, bool (*myTrigger)(void), void (*myTarget)(void));
        int createElement(Event* newEvent);
        void checkEvents();
        void map();
    };

    class Graphics {
    private:
        int width;
        int height;
        int bpp;
        bool windowOk;
        bool isWindowed;
        SDL_Window* window;
        SDL_GLContext context;
        //SDL_Surface * screen;
        SDL_Color bgColor;
        //SDL_sem * screenLock;
    protected:
    public:
        Typewriter* hTypewriter;

        Graphics();
        ~Graphics();
        bool setScreen(int newHeight, int newWidth, int newBpp);
        bool declareSettings();
        bool toggleFullscreen();
        static void printAttributes();
        void resize(int width, int height);
        void swapBuffers();
        void clearScreen();

        // Accessors
        int getWidth() { return width; }
        int getHeight() { return height; }
        int getBpp() { return bpp; }
        bool getWindowed() { return isWindowed; }
        float getAspectRatio() { return float(width) / float(height); }

        // Rendering
        void testLoop();
        void drawCube(float xPos, float yPos, float zPos);
        void drawTexturedCube(float xPos, float yPos, float zPos);

        // Manage mode
        void go2d();
        void go3d();
        void go3d(Camera* cam);
    };

    class Keyboard {
    private:
        bool map[312];
        bool prevMap[312];
        SDL_Event event;
    protected:
    public:
        Keyboard();
        void update();
        void update(SDL_Event eve);
        bool checkPressDown(char key);
        bool checkLiftUp(char key);
        bool checkPrevKey(char key);
        bool checkKey(char key);
        bool checkKey(SDL_Keycode aKey);
        KeyState checkState();
    };

    class Light {
    private:
        KirkMath::Quat * position;	// Defined within parent frame; global frame by default
        KirkMath::Quat * ambient;	// Color of ambient (non-directional) light
        KirkMath::Quat * diffuse;	// Color of diffuse (directional) light
        Light* next;
        float attenuation;	// Light attenuation factor
        int lightId;
        bool isEnabled;		// Lights are disabled by default
        bool isDirectional; // Directional lights produce parallel rays in the _position direction; non-directional lights are positional, where _position specifies the light location in the world
        bool isVisible;		// Visible lights are rendered as small points with the light's ambient color
        Mesh* lightObject;
    protected:
    public:
        // Constructors
        Light();
        ~Light();
        
        // Access
        void enable();
        void disable();
        bool getStatus() { return isEnabled; }
        bool getVisible() { return isVisible; }
        void setVisible(bool v) { isVisible = v; }
        
        // Lighting
        void setAmbient(float r, float g, float b);
        void setDiffuse(float r, float g, float b);
        void setPosition(float x, float y, float z);
        void setAttenuation(float a) { attenuation = a; }
        void setDirectional() { isDirectional = true; }
        void setPositional() { isDirectional = false; }
        void refreshPosition();
        
        // List methods
        Light * get(int n); // n < 0 returns first; n > length returns last
        void set(Light * value, int n); // n > length and n < 0 sets last
        int listLength();
        int getGLLightNum(int n);
    };

    class Mesh {
    private:
        int _numVertices;
        Vertex* _vertices;
        Vertex* _normals;
        TexCoord* _texCoords;
    protected:
    public:
        // Constructors
        Mesh();
        ~Mesh();
        
        // Loaders
        bool loadCube(float size); // Loads vertices defining size x size x size cube, where size is the length of one side.
        bool loadTetra(float size); // Loads vertices defining size x size x size tetrahedral, where size is the length of one side
        bool loadSphere(float size, int numFaces); // Loads vertices defining sphere with radius size and the given number of faces
        
        // Methods
        void clear();
        void render();
        void setColor(float r, float g, float b, float a);
        void refreshNormals();
        void debug();
        void disableTexture();
    };

    class Model {
    private:
    protected:
    public:
    };

    class Mouse {
    private:
        int currX;
        int currY;
        int prevX;
        int prevY;
        MouseState currState;
        MouseState prevState;
    protected:
    public:
        Mouse(void);
        ~Mouse(void);
        void update();
        void update(SDL_Event eve);

        int getCurrX() { return currX; }
        int getCurrY() { return currY; }
        int getPrevX() { return prevX; }
        int getPrevY() { return prevY; }
        int getDX() { return currX - prevX; }
        int getDY() { return currY - prevY; }
        ScreenDimension getXCoord();
        ScreenDimension getYCoord();
        MouseState getCurrState() { return currState; }
        MouseState getPrevState() { return prevState; }
    };

    class Object {
    private:
    protected:
        KirkMath::Trans* frame;
        KirkMath::Quat* linearVelocity; // Defined in parent frame
        KirkMath::Quat* angularVelocity; // Defined in parent frame, valued quaternion rotation
        Object* parent;
        Object* children;
        Object* next;
        Color* ambientMaterial;
        Color* diffuseMaterial;
        Texture* tex;
        Mesh* mesh;
    public:
        // Data
        bool isVisible;

        // Constructors
        Object(Object* p = NULL);
        Object(float x, float y, float z, Object* p = NULL);
        Object(KirkMath::Quat orientation, Object* p = NULL);
        Object(float x, float y, float z, KirkMath::Quat orientation, Object* p = NULL);
        ~Object();
        void freeChildren();
        
        // Access
        KirkMath::Trans getFrame();
        KirkMath::Quat getLocation();
        KirkMath::Quat getRotation();
        KirkMath::Quat getLinearVelocity();
        KirkMath::Quat getAngularVelocity();
        KirkMath::Quat getScaling();
        
        // Color
        void setAmbient(float r, float g, float b);
        void setDiffuse(float r, float g, float b);
        
        void setTexture(ArtemisUtility::String filename);
        void setTexture(SDL_Surface* surf);
        void setScaling(float x, float y, float z);
        // TEMPORARY, FOR DEMO; end class will allow manipulation only through physics forces
        void setPosition(float x, float y, float z);
        void setRotation(float w, float x, float y, float z);
        void setLinearVelocity(float x, float y, float z);
        void setAngularVelocity(float w, float x, float y, float z);
            
        // Methods
        virtual void update(float dt, bool updateChildren = true);
        virtual void render(bool renderChildren = true);
        
        // Child manipulation
        void addChild(Object* newChild);
        
        // Listing
        Object* get(int n); // n < 0 returns first; n > length returns last
        void set(Object* value, int n); // n > length and n < 0 sets last
        int listLength();
    };
    
    class Panel {
    private:
    protected:
        Panel* next;		// Subsequent siblings
        Panel* children;	// Panels rendered relative to this one
        Texture* tex;
        Color* bgColor;
        ScreenDimension x;
        ScreenDimension y;
        ScreenDimension w;
        ScreenDimension h;
        bool visible;
    public:
        bool isTranslucent;

        // Constructors
        Panel();
        Panel(float nx, float ny, float nw, float nh);
        ~Panel();

        // Virtual functions
        virtual void update(float dt);
        virtual void render(Graphics* context);
        virtual void setImage(ArtemisUtility::String filename);
        virtual void setImage(SDL_Surface* surf);
        
        // Listing
        Panel* get(int n);
        void set(Panel* value);
        int listLength();

        // Accessors
        ScreenDimension getX() { return x; }
        ScreenDimension getY() { return y; }
        ScreenDimension getW() { return w; }
        ScreenDimension getH() { return h; }
        bool getVisible() { return visible; }
        void setX(float v);
        void setY(float v);
        void setW(float v);
        void setH(float v);
        void setVisible(bool v);
        void setBgColor(float r, float g, float b, float a);

        // Collision Detection
        bool isWithin(ScreenDimension xCoord, ScreenDimension yCoord, Graphics* context);
    };

    class Soundboard {
    private:
        bool isInit;
        int audioRate;
        int audioFormat;
        int numChannels;
        int bufferSize;
        int fadeLength; // Length of fade effects, in ms
        float volume;
    protected:
    public:
        Soundboard();
        ~Soundboard();

        // Sound effects
        Mix_Chunk* loadSound(ArtemisUtility::String filename);
        void playSound(ArtemisUtility::String filename);
        void playSound(Mix_Chunk* sound);

        // Music songs
        Mix_Music* loadSong(ArtemisUtility::String filename);
        void playSong(ArtemisUtility::String filename);
        void playSong(Mix_Music* mus);
        void stopSong();
        bool isPlaying();
        bool repeatSongs;
    };

    class Stopwatch {
    private:
        // Reference only: not accurate enough for timers
        time_t currTime;
        time_t lastTime;
        int currTicks;
        int lastTicks;
        tm currTimeInfo;
        long frame;
        float dt;
        // Timers only: too high of an overhead for frequent reference usage
    protected:
    public:
        // Reference only: not accurate enough for timers
        Stopwatch();
        void refresh();
        float getFramerate();
        float getDt() { return dt; }
        ArtemisUtility::String getDayText();
        ArtemisUtility::String getMonthText();
        int getDayOfWeek();
        int getDayOfMonth();
        int getDayOfYear();
        int getHour();
        int getMinute();
        int getSecond();
        int getYear();
        ArtemisUtility::String getFullTime();
        ArtemisUtility::String getTimestamp();
        // Timers only: too high of an overhead for frequent reference usage
    };

    class TexCoord {
    public:
        float u;
        float v;
    };

    class Texture {
    private:
        GLuint _textureId;
        SDL_Surface * _texture;
        bool _isLoaded;
    public:
        Texture();
        ~Texture();
        bool loadFromFile(ArtemisUtility::String filename);
        bool loadFromSurface(SDL_Surface* surf);
        bool unload();
        bool isLoaded() { return _isLoaded; }
        bool bind();
        bool unbind();
        int getId() { return _textureId; }
    };

    class Typewriter {
    private:
        TTF_Font* currFont;
        ArtemisUtility::String currFontName;
        Color* color;
        ScreenDimension cursorX;
        ScreenDimension cursorY;
        ScreenDimension fontSize;
        int nextpoweroftwo(int x);
        
    protected:
    public:
        Typewriter();
        ~Typewriter();
        bool setFont(ArtemisUtility::String fontName);
        bool setColor(float r, float g, float b);
        void setFontSize(float fs);
        float getFontSize() { return fontSize.value; }
        bool stamp(ArtemisUtility::String text);
        bool type(ArtemisUtility::String text, int contextWidth, int contextHeight);
        void moveCursor(ScreenDimension x, ScreenDimension y); // Moves cursor to given screen coordinates
    };
    
    class Vertex {
    public:
        float x;
        float y;
        float z;
        
        Vertex();
        Vertex(float px, float py, float pz);
        void set(float px, float py, float pz);
        float mag();
        Vertex operator- (Vertex operand);
        bool operator== (Vertex operand);
        Vertex cross(Vertex operand);
        Vertex norm();
        void print();
    };

    // --- SUBCLASSES --- //
    class Console : public Panel {
    private:
        ConsoleLine * lines;
        ScreenDimension speed; // Speed at which console is animated {unit / sec)
        ScreenDimension limit; // Limit (from top of screen) of visible console
        ArtemisUtility::String font;
        ArtemisBase::Color fontColor;
        float fontSize;
    protected:
    public:
        ConsoleState state;
        Console();
        ~Console();
        void addLine(ArtemisUtility::String contents);
        ArtemisUtility::String getLine(int n);
        void render(Graphics * context);
        void update(float dt);
        void setFont(ArtemisUtility::String f);
        void setFontColor(float r, float g, float b);
        void setFontSize(float pct);
    };

    class Cursor : public Panel {
    private:
        Mouse* mouse;
    protected:
    public:
        Cursor(Mouse * m);
        ~Cursor(void);
        void render(Graphics * context);
    };
    
    class Skybox : public Object {
    private:
        float radius;
        int resolution;
    protected:
    public:
        Skybox();
        Skybox(float r, int n);
        void setRadius(float r);
        void setResolution(int n);
    };
}
