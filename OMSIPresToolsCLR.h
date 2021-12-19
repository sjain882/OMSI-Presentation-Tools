
// Tells the linker to only include this header once
#pragma once

// Instantiate variables
int f4FovUI;
float f4FovActValue;
float f4FovHoldValue;
bool justEnabledFOVApplication;
bool justScrolled;
bool hasFoundAddress;
bool isProcessActive;
bool isMapCurrentlyLoaded;
void ToggleF4FovEnabled();
