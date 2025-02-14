/* Copyright 2012-2014 The Pennsylvania State University
 *
 * This software was written by David Hadka and others.
 * 
 * The use, modification and distribution of this software is governed by the
 * The Pennsylvania State University Research and Educational Use License.
 * You should have received a copy of this license along with this program.
 * If not, contact <dmh309@psu.edu>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include "reservoir_operation.h"
#include "sort_ascend.h"
#include "IHA_median_inf.h"
#include "IHA_median_rel.h"
#include "Extremities_inf.h"
#include "Extremities_rel.h"
#include "Extremities_inf_BF.h"
#include "Extremities_rel_BF.h"
#include "rates_inf.h"
#include "rates_rel.h"
#include "Pulse_count_inf.h"
#include "Pulse_count_rel.h"
#include "Reversals_inf.h"
#include "Reversals_rel.h"
#include "Baseflow_inf.h"
#include "Baseflow_rel.h"
#include "Date_min_max.h"
#include "RVA_Dates_inf.h"
#include "RVA_Dates_rel.h"

#define PI 3.14159265358979323846

// Interpolation loop for evaporation calculation

double Elevation[155] 
double Area[155] 
double Capacity[155] 
float EleC,AreaC;
	
// INTERPOLATION FOR THE AREA FROM ELEVATION
	void interplELE2AREA (float Ele  )
	{
	 int i,j;
	 for (i=0;i<155;i++) 
	 {
	 if( Ele<Elevation[i+1] && Ele>=Elevation[i])
	 {     
	 float A1=Area[i];
	 float  A2=Area[i+1];
	 float El1=Elevation[i];
	 float El2=Elevation[i+1];
	 AreaC=A1+(A2-A1)/(El2-El1)*(Ele-El1);
	 break;
	 }
	 }
	 }
 
//INTERPOLATION FOR THE ELEVATION FROM STORAGE
	void interplStor2Ele ( float Sto)
	{  int i,count;
	  for (i=0; i<155;i++){
	    if(Sto<Capacity[i+1]) {
	      if  (Sto>=Capacity[i]) {
	        float El1=Elevation[i];
	        float El2=Elevation[i+1];
	        float S1=Capacity[i];
	        float S2=Capacity[i+1];
	        EleC=El1+(El2-El1)/(S2-S1)*(Sto-S1);
	       // printf("EleC = %f\n", EleC);
	        break;
	      }
	    }
	  }
	}
	
// Declaration statements
	
int nVars = 43, nObjs = 2, nConsts = 1;

double x[43];

int isim, jsim, nYear = 38, Posi, nPer = 12, TotPer;
int dcnt,ksim;
double EfRelTar[12][38], TotRelTar[12][38], CoStTar[12], SumTar[12][38];
double WA[12][38], CoSt[12][38], TotRel[12][38], IrrRel[12][38], EfRel[12][38], Spil[12][38];
double IrrRelDef[12][38], EfRelDef[12][38];
double b1[12],b2[12],b3[12],b4[12],RC2[12], RC1[12];
double HP1[12][38], HP2[12][38], HP3[12][38], HP4[12][38], RP1[12][38], RP2[12][38], RP3[12][38], RP4[12][38];
double RuleCurve2[12][38], RuleCurve3[12][38], RuleCurve4[12][38], RuleCurve5[12][38];
float  Daily_inflow_rate[38][366],Daily_Eflow_rate[38][366],Daily_spill,Daily_Eflow;
double IRZ2[12][38];
double EfZ2[12][38];

float Avg_IrrDefPer,sum_Monthly_irr_def,Avg_EfDefPer,sum_Monthly_Ef_def; 
float InsEle,InsArea,E1Loss,ELoss,ELD,Avg_storage,Gross_head,FSArea,FSElev;

double St0,StMin, StCap, StCap_live, StFin;
double IrrDef[12][38], EfDef[12][38],SumIrrDef, SumEfDef, IrrTSR, EfTSR;
double AnIrrTar, AnEfTar, SumIrrTar, SumEfTar;
double IrrDefPer[12][38], EfDefPer[12][38];
double SumIrrDefPerSq, SumEfDefPerSq, IrrMSI, EfMSI;
double muh, mum, mul,Irr_alpa,Eff_alpa;

double GroCoStTar[12]; double EF_frac[12];  // Decision variables in stage-1 model

// Input data

double monthly_inflow	=	INPUT: "Monthly reservoir inflow time series"

double Daily_inflow		=	INPUT: "Daily reservoir inflow time series"

int Month_Days			=	INPUT: "Total number of days in each month of each simulated year"
 
double daily_flow_frac	=	INPUT: "Fraction of daily flows to monthly flows"

double EfRelTarMonth 	=	INPUT: "Mean monthly flows of various hydrologic year types"

double Monthly_evap  	=	INPUT: "Monthly evaporation data"

double IrrRelTar		=	INPUT: "Monthly Irrigation release target"

int year_type			=	INPUT: "Hydrologic year type (dry=1;normal=2;wet=3)"

int st,ed; 	
int ncdays[13]  = {0,30,61,92,122,153,183,214,245,273,304,334,365};         // cumulative number of days in each month of a non-leap year
int ncldays[13] = {0,30,61,92,122,153,183,214,245,274,305,335,366};			// cumulative number of days in each month of a leap year
int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365}; // number of days in each simulation year considered

/***********************************************************************************************************************************************/

void Sim(double* x, double* f, double* cstr) {

/***********************************************************************************************************************************************/

TotPer = nYear*nPer; // Total Simulation Periods

SumIrrTar = nYear*AnIrrTar;
SumEfTar = nYear*AnEfTar;

// Live Carryover Storage Targets
for (isim=0; isim<nPer; isim++)
{
	GroCoStTar[isim]  = x[8+isim];
	CoStTar[isim] = GroCoStTar[isim] - StMin; 
	
}

// For deriving optimal Ef-low fractions corresponding to three HYTs
for (jsim=0;jsim<nYear;jsim++)
{
	
	if (year_type[jsim]==1) {
		
	for (isim=0; isim<7; isim++)
		{
		EF_frac[isim] = x[isim+22];					
		} 		
		for (isim=7; isim<12; isim++)
		{
		EF_frac[isim] = 1;
		} 				
		for (isim=0; isim<12; isim++)
		{
		EfRelTar[isim][jsim]= EfRelTarMonth[isim][jsim]*EF_frac[isim];
		} 
} 

	else if (year_type[jsim]==2) {
		
	for (isim=0; isim<7; isim++)
		{
		EF_frac[isim] = x[isim+29];					
		} 		
		for (isim=7; isim<12; isim++)
		{
		EF_frac[isim] = 1;
		} 				
		for (isim=0; isim<12; isim++)
		{
		EfRelTar[isim][jsim]= EfRelTarMonth[isim][jsim]*EF_frac[isim];
		} 
	}
	
	else {
		
		for (isim=0; isim<7; isim++)
		{
		EF_frac[isim] = x[isim+36];					
		} 		
		for (isim=7; isim<12; isim++)
		{
		EF_frac[isim] = 1;
		} 				
		for (isim=0; isim<12; isim++)
		{
		EfRelTar[isim][jsim]= EfRelTarMonth[isim][jsim]*EF_frac[isim];
		} 
	}
	
}
/***********************************************************************************************************************************************/

St0 = 0.75*CoStTar[nPer-1];

// Arbitary Variables
	
	SumIrrDef = 0;
	SumEfDef = 0;
	
	MaxIrrDefPer = 0;
	MaxEfDefPer = 0;
	
	SumIrrDefPerSq = 0;
	SumEfDefPerSq = 0;
	
	IrrSuccess = 0;
	EfSuccess = 0;
	isim = 0;
	jsim = 0;
   
// Reading the Hedging and rule curve Parameters

for (jsim=0;jsim<nYear;jsim++)
{
	for(isim=0;isim<nPer;isim++)
	{
		
		RP1[isim][jsim]  = x[0];		// For deriving TRC-4
		RP2[isim][jsim]  = x[1];		// For deriving TRC-3
		RP3[isim][jsim]  = x[2];		// For deriving TRC-2
		RP4[isim][jsim]  = x[3];		// For deriving TRC-1
			
				
		HP1[isim][jsim]  = x[4];		// Alpha 12
		HP2[isim][jsim]  = x[5];		// Alpha 11
		
		HP3[isim][jsim] = x[6];			// Alpha 22
		HP4[isim][jsim] = x[7];			// Alpha 21	
	
	
		RC2 [isim] = x[20]*CoStTar[isim]; 	// IRC
		RC1 [isim] = x[21]*RC2[isim];		// ERC
	
	
		b4[isim] =  RC2[isim]   + (CoStTar[isim]-RC2[isim]) *RP1[isim][jsim];			// TRC-4
		b3[isim] =  RC2[isim]   - (RC2[isim]-RC1[isim])		*RP2[isim][jsim];			// TRC-3
		b2[isim] =  RC1[isim]   + (b3[isim]-RC1[isim])		*RP3[isim][jsim];			// TRC-2	
	 	b1[isim] =  0.0			+ (RC1[isim]-0.0)			*RP4[isim][jsim];			// TRC-1
	 		
		RuleCurve2[isim][jsim] = b4[isim];
		RuleCurve3[isim][jsim] = b3[isim];
		RuleCurve4[isim][jsim] = b2[isim];
		RuleCurve5[isim][jsim] = b1[isim];
				
		
	}
}


// Release Policy Simulation for nYears

for(jsim=0;jsim<nYear;jsim++)
{
	
	dcnt = 0;
	
	
	for(isim=0;isim<nPer;isim++)
	{
	
	 ELoss = 0.0;
		interplStor2Ele (St0);     		// Interpolation of Elevation 
		InsEle = EleC;     				// Interpolated Elevation
        
		interplELE2AREA (InsEle);
		InsArea    = AreaC; 			// Interpolated Area       	
		
		while(1) 
		{ 	
	
			WA[isim][jsim]  = St0 + monthly_inflow[isim][jsim]-ELoss;	// calculation of water availability


// Membership function values			 	 
//==================================================================		
	 	 //  ML:b1  LU:b2  HL:b3  MU:b4		 
//=================================================================	   
	   	   
	   if (St0>RC2[isim])
	   {
	      muh  = 1.0;    }
	   else if(St0>b3[isim] && St0<=RC2[isim])
	    {	   	
	   	  muh  = (St0-b3[isim])/(RC2[isim]-b3[isim]);}   	   
	   else if(St0<=b3[isim]) 
	   {	   	
	   	  muh  = 0.0;}

//==================================================================		
	 	 //  ML:b1  LU:b2  HL:b3  MU:b4		 
//=================================================================	   
	   
	   if (St0<=b1[isim]){
	      mum  = 0.0;    }
	   else if(St0>b1[isim] && St0<=RC1[isim])
	    {	   	
	   	  mum  = (St0-b1[isim])/(RC1[isim]-b1[isim]);}
	   else if(St0>RC1[isim] && St0<=RC2[isim]) 
	   {	   	
	   	  mum  = 1.0;}  
	   else if(St0>RC2[isim] && St0<=b4[isim])
	    {	   	
	   	  mum  = (b4[isim]-St0)/(b4[isim]-RC2[isim]);}       	   
	   else if(St0>b4[isim]) 
	   {	   	
	   	  mum  = 0.0;}	   	  
	   	  
//==================================================================		
	 	 //  ML:b1  LU:b2  HL:b3  MU:b4		 
//=================================================================	    	  
	 
	  if (St0<=RC1[isim])
	   {
	      mul  = 1.0;    }
	   else if(St0>RC1[isim] && St0<=b2[isim])
	    {	   	
	   	  mul  = (b2[isim]-St0)/(b2[isim]-RC1[isim]);}   	   
	   else if(St0>b2[isim]) 
	   {	   	
	   	  mul  = 0.0;}
	  	  
//==================================================================		
	 	 //  ML:b1  LU:b2  HL:b3  MU:b4		 
//=================================================================	   
		
// 	Hedged release targets
	
	Irr_alpa = (muh*1.0+mum*HP1[isim][jsim]+mul*HP2[isim][jsim])/(muh+mum+mul);			
	Eff_alpa = (muh*1.0+mum*HP3[isim][jsim]+mul*HP4[isim][jsim])/(muh+mum+mul);								

	IRZ2[isim][jsim]  = Irr_alpa * IrrRelTar[isim];
	EfZ2[isim][jsim]  = Eff_alpa * EfRelTar[isim][jsim];
							
				
	reservoir_operation(isim,jsim,WA,EfZ2,IRZ2,CoStTar,EfRel,IrrRel,EfRelTar,IrrRelTar,CoSt,Spil);   // calling reservoir simulation module
	
	
			Avg_storage = (St0+CoSt[isim][jsim])/2; 
			interplStor2Ele (Avg_storage);     			// Interpolation of Elevation 
	        FSElev  = EleC;     						// Interpolated Elevation
	        
	        interplELE2AREA (EleC);
            FSArea    = AreaC; // Interpolated Area 
	    	E1Loss 	  = (InsArea+FSArea)*0.5*Monthly_evap[isim];
			
			
			 ELoss = ( E1Loss+ELoss)*0.5;
			
			 if(fabs(ELoss-E1Loss) < 2){   					// Iteration of Evaporation 	
   			 break;}
   			 
		}
				

// Disaggregation of monthly E-flow releases 	
	  	
         for(ksim=0;ksim<Month_Days[isim][jsim];ksim++) {  	
         
            Daily_spill                   = Spil[isim][jsim]*daily_flow_frac[jsim][dcnt];    	
			Daily_Eflow                   = EfRel[isim][jsim] *daily_flow_frac[jsim][dcnt];
		
		// mcft to ft^3/s conversion
		
		    Daily_inflow_rate[jsim][dcnt] = Daily_inflow[jsim][dcnt]*11.574;		// Input to IHA subroutines		
			Daily_Eflow_rate[jsim][dcnt]  = (Daily_Eflow + Daily_spill)*11.574;		// Input to IHA subroutines
			
				dcnt = dcnt+1;}	
			
// Calculation of deficit indices 
			
		IrrDef[isim][jsim] = IrrRelTar[isim] - IrrRel[isim][jsim];
		EfDef[isim][jsim] = EfRelTar[isim][jsim] - EfRel[isim][jsim] - Spil[isim][jsim];
		
		if (EfDef[isim][jsim]<0){
				EfDef[isim][jsim] = 0.0; 
			}	

			IrrDefPer[isim][jsim] = IrrDef[isim][jsim]*100/IrrRelTar[isim];               SumIrrDefPerSq = SumIrrDefPerSq + IrrDefPer[isim][jsim]*IrrDefPer[isim][jsim];
			EfDefPer[isim][jsim] = EfDef[isim][jsim]*100/EfRelTar[isim][jsim];             SumEfDefPerSq = SumEfDefPerSq + EfDefPer[isim][jsim]*EfDefPer[isim][jsim];		

// Resetting Initial Storage

St0 = CoSt[isim][jsim]; 
	
	}
	
}

// Average monthly deficits calculation

for(isim=0;isim<nPer;isim++)
	{
		sum_Monthly_irr_def = 0;
		sum_Monthly_Ef_def  = 0; 	 
		
		for(jsim=0;jsim<nYear;jsim++){
			sum_Monthly_irr_def = sum_Monthly_irr_def + IrrDefPer[isim][jsim]; 			
			sum_Monthly_Ef_def  = sum_Monthly_Ef_def  + EfDefPer[isim][jsim]; 
			
		}	
		Avg_IrrDefPer = sum_Monthly_irr_def/38;
		Avg_EfDefPer  = sum_Monthly_Ef_def/38; 
				 					
	    Monthly_Irrdef[isim]= Avg_IrrDefPer;
	    Monthly_Efdef[isim] = Avg_EfDefPer; 		
	}
	
// Maximum average monthly deficit calculation
	
	sort_numbers_ascending(Monthly_Irrdef,12,0); 	
	sort_numbers_ascending(Monthly_Efdef,12,0); 
	
	Max_Monthly_Irrdef  = Monthly_Irrdef[11];
	Max_Monthly_Efdef	= Monthly_Efdef[11];

// Calculation of Performance Measures - MSIs

	IrrMSI = SumIrrDefPerSq/(TotPer*100);
	EfMSI = SumEfDefPerSq/(TotPer*100);
	

/***********************************************************************************************************************************************/
	
// The necessary IHA subroutines (parameters chosen based on PCA) is invoked here - employing HCA
	
	IHA_median_inf and IHA_median_rel		// IHA group-1 monthly medians of December and January
	Extremities_inf and Extremities_rel		// IHA group-2 7-day maximum, 30-day minimum and baseflow

	
float overall_HA_HCA;					
	
overall_HA_HCA = sqrt((sqr_DCM_Dec+sqr_DCM_Jan+sqr_DCM_G27_max+sqr_DCM_G230_min+sqr_DCM_G2BF)/5);
		

/***********************************************************************************************************************************************/


// Objective functions

	isim = 0;
	f[isim] = IrrMSI;
	isim = isim+1;
	f[isim] = overall_HA_HCA;

// constraint

if (Max_Monthly_Efdef < 20.0)
{
	cstr[0] = 0;

}
else
{
	cstr[0] = Max_Monthly_Efdef - 20.0;  // Limiting constraint on maximum value of average monthly E-flow deficit to derive reliable E-flow targets 
	
}

}


