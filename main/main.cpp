#include "main.h"
#include "animate.h"
#include "timer.h"

namespace _main_ {
    
    #define DURATION_MAX 8000
    #define DURATION_MIN 1000
    #define DURATION_INC 500
    #define RATE_MAX 18
    #define RATE_MIN 2
    #define RATE_INC 2
    #define TEST_COLOR makeColorRGB(0xFF, 0xB6, 0x00)

    #define TEST_PULSE 0
    #define TEST_SPIN 1
    #define TEST_RADIATE 2
    #define TEST_FADE 3
    #define TEST_COUNT 4


    byte _fadeFunction;
    byte _testOp;
    byte _rate;
    byte _duration;

    void handleFadeSwap() {
        _fadeFunction =  (_fadeFunction + 1) % ANIMATE_FUNCTION_COUNT;
        animate::startFade();
        timer::mark(_duration, handleFadeSwap);
    }

    void setup() {
        _fadeFunction = 0;
        _testOp = 0;
    };

    
    void loop() {
        timer::loop();
        if(buttonDoubleClicked()){
            _testOp = (_testOp + 1) % TEST_COUNT;
            if(_testOp == TEST_FADE) {
                animate::startFade();
                timer::mark(_duration, handleFadeSwap);
            } else {
                timer::cancel();
            }
        }
        if(buttonSingleClicked()){
            _rate = (_rate + RATE_INC) % (RATE_MAX+1);
            _rate = max(RATE_MIN, _rate);
            _duration = (_rate + DURATION_INC) % (DURATION_MAX+1);
            _duration = max(DURATION_MIN, _rate);
        }
        if(_testOp == TEST_FADE) {
            FOREACH_FACE(f) {
                animate::fadeFace(TEST_COLOR, _duration, _fadeFunction, f);
            }
            return;
        }
        if(_testOp == TEST_PULSE) {
            animate::pulse(TEST_COLOR, _rate);
            return;
        }
        if(_testOp == TEST_RADIATE) {
            animate::radiate(TEST_COLOR, 0, _rate);
            return;
        }
        if(_testOp == TEST_SPIN) {
            animate::spin(TEST_COLOR, _rate);
        }
    }

}
