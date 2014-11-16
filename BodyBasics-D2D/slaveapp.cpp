// slaveapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <vector>
#include <Windows.h>
#include <MMsystem.h>
#include <iostream>

#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include "speaker.h"
#define NUM_SPEAKERS 2

typedef double dist;
typedef double volume;

bool ChangeVolume(double nVolume, bool bScalar)
{

	HRESULT hr = NULL;
	bool decibels = false;
	bool scalar = false;
	double newVolume = nVolume;

	CoInitialize(NULL);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	// -------------------------
	float currentVolume = 0;
	endpointVolume->GetMasterVolumeLevel(&currentVolume);
	//printf("Current volume in dB is: %f\n", currentVolume);

	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	//CString strCur=L"";
	//strCur.Format(L"%f",currentVolume);
	//AfxMessageBox(strCur);

	// printf("Current volume as a scalar is: %f\n", currentVolume);
	if (bScalar == false)
	{
		hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
	}
	else if (bScalar == true)
	{
		hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
	}
	endpointVolume->Release();

	CoUninitialize();

	return FALSE;
}
// This is the function that needs to pull data from KINECT position sensors
void getDist(dist &x, dist &y, dist &z) {
	x += 1;
	z -= 1;
	//std::cin >> x >> y >> z;
	// Interpret KINECT data to update x, y, and z position
	// Don't return, just change, since they are passed in by reference
}

// This function updates that member variable representing the volume for a certain speaker
// based on the readings of position
void update(Speaker &s, dist &x, dist &y, dist &z, const volume &L_c, const dist &x_c, const dist &y_c, const dist &z_c) {

	//std::cout << "Speaker " << s.getID() << ":\nx: " << s.getX() << ", y: " << s.getY() << ", z: " << s.getZ() << "\n";
	getDist(x, y, z);

	dist r_0 = sqrt(pow((x - s.getX()), 2) + pow((y - s.getY()), 2) + pow((z - s.getZ()), 2));
	dist r = sqrt(pow((s.getX() - x_c), 2) + pow((s.getY() - y_c), 2) + pow((s.getZ() - z_c), 2));
	//std::cout << "r_0: " << r_0 << "\nr: " << r << "\n";

	volume L_0 = L_c + 20 * log(r_0 / r);
	//std::cout << "L_c: " << L_c << "\n20*log(r0/r)" << 20 * log(r_0 / r) << "\n";

	if (L_0 > 78) { L_0 = 78; }
	if (L_0 < 0) { L_0 = 0; }

	s.setL(L_0);

	volume send_val = (pow(10, (L_0 / 20)) - 1) / 8000;
	ChangeVolume(send_val, true);
	//send value L_0 to database, 
	//std::cout << L_0 << "\n";
}

int _tmain(int argc, _TCHAR* argv[])
{

	// Variables that will be updated
	dist x = 0;
	dist y = 0;
	dist z = 6;
	dist x_c = 0;
	dist y_c = 0;
	dist z_c = 0;
	volume L_c = 60; // dB

	// Constants
	std::vector<Speaker> speakers(1);
	speakers[0] = Speaker(1, 0, 0, 0);
	//speakers[1] = Speaker(2, 100, 50, 0);

	getAverages(speakers, x_c, y_c, z_c);

	// Loop forever, update each speaker every time
	while (1) {
		for (unsigned int i = 0; i < speakers.size(); ++i) {
			update(speakers[i], x, y, z, L_c, x_c, y_c, z_c);
		}
	}
	return 0;
}