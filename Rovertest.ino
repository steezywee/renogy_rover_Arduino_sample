//RJ12 Pinout
//1 White TX
//2 Black RX
//3 Red GND
//4 Green GND
//5 Yellow +15V
//6 Green +15V


#define MODBUS_SERIAL Serial   //Renogy Rover Com Port
#include "RenogyRover.h"        //For some reason it wasn't recognized as a library.
                                //ModbusMaster.h is also required. Available from Manage Arduino Libraries
RenogyRover rover;
PanelState panel;
BatteryState battery;
DayStatistics daystat;
HistStatistics histstat;
ChargingState chargestat;
char* model="0000000000000000";//16 bytes, so 15 characters
FaultCode* faultcode;
int numerr = 0;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);   //Rover's genuine communication unit (BT-1) is 9600bps
  rover.begin(9600);
  
  if(rover.getProductModel(model))      //Model number acquisition (RNG-CTRL-RVR20)
  {
    Serial.println(model);
  }
  else
  {
    Serial.println("modelgetERROR");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("------------------------------------------------");
  if(rover.getPanelState(&panel))      //Get panel status
  {
    Serial.print("PV=,");
    Serial.print(panel.voltage);
    Serial.print(",V, PI=,");
    Serial.print(panel.current);
    Serial.print(",A, PP=,");
    Serial.print(panel.chargingPower);
    Serial.println(",W");
  }
  else
  {
    Serial.println("panelgetERROR");
  }

  if(rover.getBatteryState(&battery))      //Get battery status
  {
    Serial.print("BV=,");
    Serial.print(battery.batteryVoltage);
    Serial.print(",V, BchgI=,");
    Serial.print(battery.chargingCurrent);
    Serial.print(",A, CHGCap=,");
    Serial.print(battery.stateOfCharge);
    Serial.print(",%, CTRLTMP=,");
    Serial.print(battery.controllerTemperature);
    Serial.print(",C, BTMP=,");
    Serial.print(battery.batteryTemperature);
    Serial.println(",C");
  }
  else
  {
    Serial.println("batterygetERROR");
  }

  if(rover.getDayStatistics(&daystat))      //Get day statistics
  {
    Serial.print("DAY:minBV=,");
    Serial.print(daystat.batteryVoltageMinForDay);
    Serial.print(",V, maxBV=,");
    Serial.print(daystat.batteryVoltageMaxForDay);
    Serial.print(",V, maxchgI=,");
    Serial.print(daystat.maxChargeCurrentForDay);
    Serial.print(",A, maxDischgI=,");
    Serial.print(daystat.maxDischargeCurrentForDay);
    Serial.print(",A, maxchgP=,");
    Serial.print(daystat.maxChargePowerForDay);
    Serial.print(",W, maxDischgP=,");
    Serial.print(daystat.maxDischargePowerForDay);
    Serial.print(",W, chgAH=,");
    Serial.print(daystat.chargingAmpHoursForDay);
    Serial.print(",AH, DischgAH=,");
    Serial.print(daystat.dischargingAmpHoursForDay);
    Serial.print(",AH, GenWH=,");
    Serial.print(daystat.powerGenerationForDay);
    Serial.print(",WH, 消費電力量=,");
    Serial.print(daystat.powerConsumptionForDay);
    Serial.println(",WH");
  }
  else
  {
    Serial.println("daystatgetERROR");
  }

  if(rover.getHistoricalStatistics(&histstat))      //Get historical stats
  {
    Serial.print("Operating Days=,");
    Serial.print(histstat.operatingDays);
    Serial.print(",d, Overdischarges=,");
    Serial.print(histstat.batOverDischarges);
    Serial.print(", Full Charges=,");
    Serial.print(histstat.batFullCharges);
    Serial.print(", Total Charging Amp Hrs=,");
    Serial.print(histstat.batChargingAmpHours);
    Serial.print(",AH, Total Discharge Amp Hrs=,");
    Serial.print(histstat.batDischargingAmpHours);
    Serial.print(",AH, Total Power Generated=,");
    Serial.print(histstat.powerGenerated);
    Serial.print(",kWH, Total Power Consumed=,");
    Serial.print(histstat.powerConsumed);
    Serial.println(",kWH");
  }
  else
  {
    Serial.println("histstatgetERROR");
  }

  if(rover.getChargingState(&chargestat))      //充電状況
  {
    Serial.print("Sunlight State=,");
    Serial.print(chargestat.streetLightState);
    Serial.print(", Sunlight Brightness=,");
    Serial.print(chargestat.streetLightBrightness);
    Serial.print(", Charging Mode,");
    switch(chargestat.chargingMode)
    {
      case UNDEFINED:
        Serial.print("UNDEFINED");
        break;
      case DEACTIVATED:
        Serial.print("DEACTIVATED");
        break;
      case ACTIVATED:
        Serial.print("ACTIVATED");
        break;
      case MPPT:
        Serial.print("MPPT");
        break;
      case EQUALIZING:
        Serial.print("EQUALIZING");
        break;
      case BOOST:
        Serial.print("BOOST");
        break;
      case FLOATING:
        Serial.print("FLOATING");
        break;
      case OVERPOWER:
        Serial.print("OVERPOWER");
        break;
      default:
        Serial.print("UNDEFINED");
    }
    
    Serial.println("");
  }
  else
  {
    Serial.println("chargestatgetERROR");
  }
/*
 * I dont understand
 * int getErrors(FaultCode*& errors, int& numErrors);
 * 
  if(rover.getErrors(*faultcode,&numerr))      //Get Errors
  {
    
  }
  else
  {
    Serial.println("Error get ERROR");
  }
*/
  //int setStreetLight(int state);    //There is also
  delay(500);
}
