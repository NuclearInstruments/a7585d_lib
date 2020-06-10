#include <inttypes.h>
#include <Arduino.h>
#include <Wire.h>

#include "A7585lib.h"

 #define NIPMREG_HVSTATUS 0 
 #define NIPMREG_FBMODE 1
 #define NIPMREG_VTARGET 2
 #define NIPMREG_RAMP 3
 #define NIPMREG_MAXV 4
 #define NIPMREG_MAXI 5
 #define NIPMREG_MAXT 6
 #define NIPMREG_TEMP_M2 7
 #define NIPMREG_TEMP_M 8
 #define NIPMREG_TEMP_Q 9
 #define NIPMREG_ALFA_V 10
 #define NIPMREG_ALFA_I 11
 #define NIPMREG_ALFA_VREF 12
 #define NIPMREG_ALFA_TREF 13
 #define NIPMREG_TCOEF 28
 #define NIPMREG_LUTENABLE 29
 #define NIPMREG_PIDENABLE 30
 #define NIPMREG_EMERGENCYSTOP 31
 #define NIPMREG_IZERO 33
 #define NIPMREG_LUTADDRESS 36
 #define NIPMREG_LUTT 37
 #define NIPMREG_LUTV 38
 #define NIPMREG_POINTn 39
 #define NIPMREG_IIC_BA 40
 
 #define NIPMREG_UNDERVOLTAGE 227
 #define NIPMREG_NTCTEMP 228
 #define NIPMREG_DIGITALIO 229
 #define NIPMREG_VIN 230
 #define NIPMREG_VOUT 231
 #define NIPMREG_IOUT 232
 #define NIPMREG_VREF 233
 #define NIPMREG_TREF 234
 #define NIPMREG_VTARGET_R 235
 #define NIPMREG_RTARGET_R 236
 #define NIPMREG_CORRECTIONVOLTAGE 237
 #define NIPMREG_PIDOUT 238
 #define NIPMREG_COMPV 249
 #define NIPMREG_COMPI 250
 
 #define NIPMREG_PDCODE 251
 #define NIPMREG_FWVER 252
 #define NIPMREG_HWVER 253
 #define NIPMREG_SN 254
 #define NIPMREG_WEEPROM 255
 
  bool A7585::Init(int IICAddress)
  {
	  uint32_t pd;
	  uint32_t sn;
	  Wire.begin();
	  address = IICAddress;
	  
	  GetNIPMRegInteger(address, NIPMREG_PDCODE, &pd);	  
	  GetNIPMRegInteger(address, NIPMREG_PDCODE, &sn);
	  
	  
	  if ((pd==50) || (pd==51) || (pd==52) || (pd==53) || (pd==54) || (pd==55) || (pd==56) ||(pd==1))
	  {
		  return true;
	  }
	  else
		  return false;
  }
  void A7585::Set_V(float v)
  {
	  SetNIPMRegFloat(address, NIPMREG_VTARGET, v);
  }
  void A7585::Set_MaxV(float v)
  {
	  SetNIPMRegFloat(address, NIPMREG_MAXV, v);
  }
  void A7585::Set_MaxI(float v)
  {
	  SetNIPMRegFloat(address, NIPMREG_MAXI, v);
  }
  void A7585::Set_Enable(bool on)
  {
	  SetNIPMRegBoolean(address, NIPMREG_HVSTATUS, on);
  }
  void A7585::Set_RampVs(float vs)
  {
	  SetNIPMRegFloat(address, NIPMREG_RAMP, vs);
  }
  void A7585::Set_Mode(HVFeedbackMode fbmode)
  {
	  SetNIPMRegInteger(address, NIPMREG_FBMODE, (int) fbmode);
  }
  void A7585::Set_TemperatureSensor(HVTemperatureSensors SensorModel, float term_m2, float term_m, float term_q )
  {
	  if (SensorModel==TMP100)
	  {
		  SetNIPMRegFloat(address, NIPMREG_TEMP_M2, 0);
		  SetNIPMRegFloat(address, NIPMREG_TEMP_M, 50);
		  SetNIPMRegFloat(address, NIPMREG_TEMP_Q, 0);
	  }

	  if (SensorModel==LM94021)
	  {
		  SetNIPMRegFloat(address, NIPMREG_TEMP_M2, 0);
		  SetNIPMRegFloat(address, NIPMREG_TEMP_M, -73.53);
		  SetNIPMRegFloat(address, NIPMREG_TEMP_Q, 193.9);
	  }
	  
	  if (SensorModel==CUSTOM_SENSOR)
	  {
		  SetNIPMRegFloat(address, NIPMREG_TEMP_M2, term_m2);
		  SetNIPMRegFloat(address, NIPMREG_TEMP_M, term_m);
		  SetNIPMRegFloat(address, NIPMREG_TEMP_Q, term_q);
	  }
	  
	  
  }
  void A7585::Set_Filter(float alfa_v, float alfa_i, float alfa_t)
  {
	  SetNIPMRegFloat(address, NIPMREG_ALFA_V, alfa_v);
	  SetNIPMRegFloat(address, NIPMREG_ALFA_I, alfa_i);
	  SetNIPMRegFloat(address, NIPMREG_ALFA_TREF, alfa_t);
  }
  void A7585::Set_SiPM_Tcoef (float tcomp)
  {
	  SetNIPMRegFloat(address, NIPMREG_TCOEF, tcomp);
  }
  void A7585::EmergencyOff()
  {
	  SetNIPMRegBoolean(address, NIPMREG_EMERGENCYSTOP, 1);
  }
  void A7585::SetI0()
  {
	  SetNIPMRegBoolean(address, NIPMREG_IZERO, 1);
  }
  void A7585::Set_DigitalFeedback(bool on)
  {
	  SetNIPMRegBoolean(address, NIPMREG_PIDENABLE, on);
  }
  void A7585::Set_IIC_baseaddress(uint8_t ba)
  {
	  SetNIPMRegInteger(address, NIPMREG_IIC_BA, (int) ba);
  }
  
  uint8_t A7585::GetDigitalPinStatus()
  {
	  uint32_t II;
	  GetNIPMRegInteger(address, NIPMREG_DIGITALIO, &II);
	  return II;
  }
  float A7585::GetVin()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_VIN, &v);
	  return v;
  }
  float A7585::GetVout()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_VOUT, &v);
	  return v;
  }
  float A7585::GetIout()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_IOUT, &v);
	  return v;
  }
  float A7585::GetVref()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_VREF, &v);
	  return v;
  }
  float A7585::GetTref()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_TREF, &v);
	  return v;	  
  }
  float A7585::GetVtarget()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_VTARGET_R, &v);
	  return v;	  
  }
  float A7585::GetVCurrentSP()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_RTARGET_R, &v);
	  return v;	  
	  
  }
  float A7585::GetVcorrection()
  {
	  float v;
	  GetNIPMRegFloat(address, NIPMREG_CORRECTIONVOLTAGE, &v);
	  return v;	  
  }
  
  bool A7585::GetVCompliance()
  {
	  bool v;
	  GetNIPMRegBoolean(address, NIPMREG_COMPV, &v);
	  return v;	  	  
  }
  bool A7585::GetICompliance()
  {
	  bool v;
	  GetNIPMRegBoolean(address, NIPMREG_COMPI, &v);
	  return v;	  	  	  
  }
  
  uint8_t A7585::GetProductCode()
  {
	  uint32_t II;
	  GetNIPMRegInteger(address, NIPMREG_PDCODE, &II);
	  return II;
  }
  uint8_t A7585::GetFWVer()
  {
	  uint32_t II;
	  GetNIPMRegInteger(address, NIPMREG_FWVER, &II);
	  return II;
  }
  uint8_t A7585::GetHWVer()
  {
	  uint32_t II;
	  GetNIPMRegInteger(address, NIPMREG_HWVER, &II);
	  return II;	  
  }
  uint32_t A7585::GetSerialNumber()
  {
	  uint32_t II;
	  GetNIPMRegInteger(address, NIPMREG_SN, &II);
	  return II;	  
  }
  
  bool A7585::GetHVOn()
  {
	  bool v;
	  GetNIPMRegBoolean(address, NIPMREG_HVSTATUS, &v);
	  return v;	  
  }

  bool A7585::GetConnectionStatus()
  {
	  uint32_t pd;
	  GetNIPMRegInteger(address, NIPMREG_PDCODE, &pd);
	  GetNIPMRegInteger(address, NIPMREG_PDCODE, &pd);
	  GetNIPMRegInteger(address, NIPMREG_PDCODE, &pd);
	  GetNIPMRegInteger(address, NIPMREG_PDCODE, &pd);
	  if ((pd==50) || (pd==51) || (pd==52) || (pd==53) || (pd==54) || (pd==55) || (pd==56) ||(pd==1))
	  {
		  return true;
	  }
	  else
		  return false;
  }
  
  void A7585::StoreCfgOnFlash()
  {
	  SetNIPMRegBoolean(address, NIPMREG_WEEPROM, 1);
  }
  
  
  
  
void A7585::SetNIPMRegFloat(int device_address, uint8_t register_n, float data)
{
  uint8_t vv[16];
  vv[0] = register_n;
  vv[1] = 3;
  memcpy(&vv[2], &data, 4);
  Wire.beginTransmission(device_address); 
  Wire.write(vv[0]); 
  Wire.write(vv[1]); 
  Wire.write(vv[2]); 
  Wire.write(vv[3]); 
  Wire.write(vv[4]); 
  Wire.write(vv[5]); 
  Wire.endTransmission();   
}

void A7585::SetNIPMRegBoolean(int device_address, uint8_t register_n, bool data)
{
  uint8_t vv[16];
  vv[0] = register_n;
  vv[1] = 2;
  vv[2] = data == true ? 1 : 0;
  vv[3] = 0;
  vv[4] = 0;
  vv[5] = 0;
  Wire.beginTransmission(device_address); 
  Wire.write(vv[0]); 
  Wire.write(vv[1]); 
  Wire.write(vv[2]); 
  Wire.write(vv[3]); 
  Wire.write(vv[4]); 
  Wire.write(vv[5]); 
  Wire.endTransmission();   
}

void A7585::SetNIPMRegInteger(int device_address, uint8_t register_n, int32_t data)
{
  uint8_t vv[16];
  vv[0] = register_n;
  vv[1] = 0;
  memcpy(&vv[2], &data, 4);
  Wire.beginTransmission(device_address); 
  Wire.write(vv[0]); 
  Wire.write(vv[1]); 
  Wire.write(vv[2]); 
  Wire.write(vv[3]); 
  Wire.write(vv[4]); 
  Wire.write(vv[5]); 
  Wire.endTransmission();   
}

void A7585::GetNIPMRegFloat(int device_address, uint8_t register_n, float *data)
{
  int i;
  i=0;
  uint8_t vv[16];
  vv[0] = register_n;
  vv[1] = 3;
  Wire.beginTransmission(device_address); 
  Wire.write(vv[0]); 
  Wire.write(vv[1]); 
  Wire.requestFrom(device_address, 4);   
  i=0;
  while (Wire.available()) {
    vv[i] = Wire.read(); 
    i++;
  }  
  Wire.endTransmission();   
  memcpy(data,vv,4);
}

void A7585::GetNIPMRegBoolean(int device_address, uint8_t register_n, bool *data)
{
  uint8_t vv[16];
  vv[0] = register_n;
  vv[1] = 2;
  int i;
  Wire.beginTransmission(device_address); 
Wire.beginTransmission(device_address); 
  Wire.write(vv[0]); 
  Wire.write(vv[1]); 
  Wire.requestFrom(device_address, 4);   
  i=0;
  while (Wire.available()) {
    vv[i] = Wire.read(); 
    i++;
  }  
  Wire.endTransmission();   
  *data = vv[0];
}

void A7585::GetNIPMRegInteger(int device_address, uint8_t register_n, int32_t *data)
{
  int i;
  uint8_t vv[16];
  vv[0] = register_n;
  vv[1] = 0;
  Wire.beginTransmission(device_address); 
  Wire.write(vv[0]); 
  Wire.write(vv[1]); 
  Wire.requestFrom(device_address, 4);   
  i=0;
  while (Wire.available()) {
    vv[i] = Wire.read(); 
    i++;
  }  
  Wire.endTransmission();   
  memcpy(data,vv,4);
}

