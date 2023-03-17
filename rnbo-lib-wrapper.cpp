/*
    python wrapper for Max RNBO exported C++
    rama gottfried, icst zhdk 2023
*/

#include <iostream>
#include <memory>
#include "RNBO.h"

#define WIN_DECLSPEC
#ifdef WIN32
#define WIN_DECLSPEC __declspec(dllexport)
#endif

/** globals **/
int sampleRate = 48000;
int vectorSize = 64;
std::unique_ptr<RNBO::CoreObject> rnboObject; // the RNBO object
std::vector<RNBO::SampleValue> retVec; // state holder for return vector to python


extern "C" {

WIN_DECLSPEC void init(int sr, int vs)
{
    rnboObject = std::make_unique<RNBO::CoreObject>();

    sampleRate = sr;
    vectorSize = vs;

    retVec.resize(vs);
    rnboObject->prepareToProcess(sr, vs);
}

WIN_DECLSPEC bool validObject()
{
    if(!rnboObject.get()){
        std::cout << "error: RNBO object must be initialized before use -- to initialize call: init(samplerate, vectorsize)";
        return 0;
    }
    return 1;
}


// https://rnbo.cycling74.com/learn/getting-and-setting-parameters-cpp

WIN_DECLSPEC void printInfo()
{
    if( !validObject() ) return;

    int n = rnboObject->getNumParameters();
    for (int i = 0; i < n; i++) {
        const char *id = rnboObject->getParameterId(i);

        RNBO::ParameterInfo info;
        rnboObject->getParameterInfo(i, &info);

        std::cout << i << ":\t" << id << 
            "\n\t(min:" << info.min << ", max:" << info.max << ")\n" <<
            "\tcurrent value: " <<  rnboObject->getParameterValue(i) << "\n\n";

    }
// add number of channels
// what else?

}


WIN_DECLSPEC void clearState() {
    if( !validObject() ) return;

    rnboObject->prepareToProcess(sampleRate, vectorSize);
}


WIN_DECLSPEC RNBO::SampleValue* rnbo_process_vec()
{
    if( !validObject() ) return nullptr;

    RNBO::SampleValue* ptrVec = retVec.data();

    rnboObject->process<RNBO::SampleValue**, RNBO::SampleValue**>(nullptr, 0, &ptrVec, 1, vectorSize);

    return retVec.data();

}

// set-get by Id
WIN_DECLSPEC void setParamValueById(const char* id, double val) 
{    
    if( !validObject() ) return;

    int parameterIndex = rnboObject->getParameterIndexForID(id);
    rnboObject->setParameterValue(parameterIndex, val);
}

WIN_DECLSPEC double getParamValueById(const char* id) 
{    
    if( !validObject() ) return 0;

    int parameterIndex = rnboObject->getParameterIndexForID(id);
    return rnboObject->getParameterValue(parameterIndex);
}

WIN_DECLSPEC void setNormParamValueById(const char* id, double val) 
{    
    if( !validObject() ) return;

    int parameterIndex = rnboObject->getParameterIndexForID(id);
    rnboObject->setParameterValueNormalized(parameterIndex, val);
}

WIN_DECLSPEC double convertFromNormParamValueById(const char* id, double val) 
{    
    if( !validObject() ) return 0;

    int parameterIndex = rnboObject->getParameterIndexForID(id);
    return rnboObject->convertFromNormalizedParameterValue(parameterIndex, val);
}

// set-get by Idx

WIN_DECLSPEC void setParamValueByIdx(int idx, double val) 
{
    if( !validObject() ) return;

    rnboObject->setParameterValue(idx, val);
}

WIN_DECLSPEC double getParamValueByIdx(int idx) 
{    
    if( !validObject() ) return 0;

    return rnboObject->getParameterValue(idx);
}

WIN_DECLSPEC void setNormParamValueByIdx(int idx, double val) 
{    
    if( !validObject() ) return;

    rnboObject->setParameterValueNormalized(idx, val);
}

WIN_DECLSPEC double convertFromNormParamValueByIdx(int idx, double val) 
{    
    if( !validObject() ) return 0;

    return rnboObject->convertFromNormalizedParameterValue(idx, val);
}

// https://rnbo.cycling74.com/learn/getting-and-setting-parameters-cpp


// https://rnbo.cycling74.com/learn/sending-and-receiving-midi-cpp

WIN_DECLSPEC void midiEvent(int midiNote, int midiVelocity) 
{
    if( !validObject() ) return;

    const uint8_t noteOn = 0x90;
    const uint8_t midiChannel = 0;

    const uint8_t noteOnLeadByte = noteOn | midiChannel;
    const uint8_t pitch = midiNote;
    const uint8_t velocity = midiVelocity; // probably need to clamp 0-127

    const uint8_t midiBytes[3] = { noteOnLeadByte, pitch, velocity };
    rnboObject->scheduleEvent(RNBO::MidiEvent(RNBO::RNBOTimeNow, 0, midiBytes, 3));
}


}


