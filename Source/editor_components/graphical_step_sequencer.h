/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_9CB049E4401FF7BE__
#define __JUCE_HEADER_9CB049E4401FF7BE__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include <vector>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GraphicalStepSequencer  : public Component
{
public:
    //==============================================================================
    GraphicalStepSequencer (int num_steps);
    ~GraphicalStepSequencer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setNumSteps(int num_steps);
    void changeStep(const MouseEvent& e);
    int getHoveredStep(float x_position);
    void updateHover(int step_index);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void mouseMove (const MouseEvent& e);
    void mouseExit (const MouseEvent& e);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int num_steps_;
    int highlighted_step_;
    std::vector<float> sequence_;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicalStepSequencer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9CB049E4401FF7BE__