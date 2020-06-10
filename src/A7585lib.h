#ifndef DT5485LIB_H
#define DT5485LIB_H

#include "Arduino.h"
#include <inttypes.h>


class A7585
{
   private:
      int address;  // pin utilizzato per pilotare il LED
	  void SetNIPMRegFloat(int device_address, uint8_t register_n, float data);
	  void SetNIPMRegBoolean(int device_address, uint8_t register_n, bool data);
      void SetNIPMRegInteger(int device_address, uint8_t register_n, int32_t data);
	  void GetNIPMRegFloat(int device_address, uint8_t register_n, float *data);
	  void GetNIPMRegBoolean(int device_address, uint8_t register_n, bool *data);
	  void GetNIPMRegInteger(int device_address, uint8_t register_n, int32_t *data);

   public:
	  enum HVFeedbackMode {
		  HVFB_digital=0,
		  HVFB_analog=1,
		  HVFB_temperature=2
		};
		
	  enum HVTemperatureSensors {
		  TMP100,
		  LM94021,
		  CUSTOM_SENSOR
		};		
      
	  bool Init(int IICAddress);
      void Set_V(float v);
	  void Set_MaxV(float v);
	  void Set_MaxI(float v);
	  void Set_Enable(bool on);
	  void Set_RampVs(float vs);
	  void Set_Mode(HVFeedbackMode fbmode);
	  void Set_TemperatureSensor(HVTemperatureSensors SensorModel, float term_m2, float term_m, float term_q );
	  void Set_Filter(float alfa_v, float alfa_i, float alfa_t);
	  void Set_SiPM_Tcoef (float tcomp);
	  void EmergencyOff();
	  void SetI0();
	  void Set_DigitalFeedback(bool on);
	  void Set_IIC_baseaddress(uint8_t ba);
	  
	  uint8_t GetDigitalPinStatus();
	  float GetVin();
	  float GetVout();
	  float GetIout();
	  float GetVref();
	  float GetTref();
	  float GetVtarget();
	  float GetVCurrentSP();
	  float GetVcorrection();
	  
	  bool GetVCompliance();
	  bool GetICompliance();
	  
	  uint8_t GetProductCode();
	  uint8_t GetFWVer();
	  uint8_t GetHWVer();
	  uint32_t GetSerialNumber();
	  
	  bool GetHVOn();
      bool GetConnectionStatus();
  
	  void StoreCfgOnFlash();
	  
};

#endif