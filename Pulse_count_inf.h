void pulse_count_inf(int year_begin,int year_end,float daily_inflow_rate[][366], 
					 float* percentile_25th,float* percentile_75th,
					 float* RVA_low_LPD, float* RVA_high_LPD, float Nexp_LPD[], 
					 float* RVA_low_LPE, float* RVA_high_LPE, float Nexp_LPE[],					  
					 float* RVA_low_HPD, float* RVA_high_HPD, float Nexp_HPD[], 
					 float* RVA_low_HPE, float* RVA_high_HPE, float Nexp_HPE[],
					 float Lopulse_event[],float Lopulse_dura[],float Hipulse_event[],float Hipulse_dura[])
 {
	
   float Daily_FLow_cnt[366*38];
   int cnt1,cnt2,cnt3,jsim,isim,nPer,st_yr,end_yr;
   int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};

   cnt1 = 0; 
   for(jsim=year_begin;jsim<year_end;jsim++)
   {    
	nPer = nyDays[jsim]; 	
	for(isim=0;isim<nPer;isim++)
	{ 
		Daily_FLow_cnt[cnt1] = daily_inflow_rate[jsim][isim];
		cnt1=cnt1+1;
		}
	}
   sort_numbers_ascending(Daily_FLow_cnt,cnt1,0);    
   float daily_flow_all[cnt1];
   
   for(jsim=year_begin;jsim<cnt1;jsim++)
   { 
   daily_flow_all[jsim] = Daily_FLow_cnt[jsim];
    } 
   
   st_yr = 0;
   end_yr= cnt1;
   
	float      p,pct,remain;
	int pct1;
   
   	    p      = 0.25;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1   =  pct1+st_yr-1;
	    *percentile_25th = daily_flow_all[pct1]+remain*(daily_flow_all[pct1+1]-daily_flow_all[pct1]);       	  	          
        p      = 0.75;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1   = pct1+st_yr-1;
	    *percentile_75th = daily_flow_all[pct1]+remain*(daily_flow_all[pct1+1]-daily_flow_all[pct1]);       	  	

// pulse count 
   int total_days;    
   total_days = 0;
   for(jsim=year_begin;jsim<year_end;jsim++)
   {
   	total_days = total_days+nyDays[jsim];
   }

   int low_pulse_count[total_days],high_pulse_count[total_days];   
   cnt1 = 0;
   
   for(jsim=year_begin;jsim<year_end;jsim++)
   {    
	nPer = nyDays[jsim]; 	
	for(isim=0;isim<nPer;isim++)
	{ 
	  if ( daily_inflow_rate[jsim][isim]<*percentile_25th){
	  	low_pulse_count[cnt1]=1;} 
	  else {
	  	low_pulse_count[cnt1]=0;}
	  	
	  if ( daily_inflow_rate[jsim][isim]>*percentile_75th){
	  	high_pulse_count[cnt1]=1;}
		  
		else {
			high_pulse_count[cnt1]=0;
		}   
	 cnt1 = cnt1+1;	 
	 
	 }
   }
  
   
//***********************************************************   
// Low pulse count 
//***********************************************************   
 

 float Event[year_end];
   float Duration[180][year_end];
   
   cnt1            =0;
   for(jsim=year_begin;jsim<year_end;jsim++)
   {    
	nPer = nyDays[jsim]; 	
	cnt2 = 0;
	cnt3 = 0;
	for(isim=0;isim<nPer;isim++)
	{ 

		 if (low_pulse_count[cnt1]>0)	 
		 {cnt2 = cnt2+1;} 
	 
		 if (low_pulse_count[cnt1]==0)
		 {if (cnt2>0)
		 {cnt3=cnt3+1;		 
		 	Duration[cnt3][jsim]=cnt2;
		 }
		 	cnt2 = 0;} 			 			 
			 
		if (low_pulse_count[cnt1]>0 && isim==nPer-1)
		 {cnt3=cnt3+1;
		 Duration[cnt3][jsim]=cnt2;	
		 }			 		 	 		 									
	     cnt1 = cnt1+1;  	 
	     
	     
	     
	 }	 
	 Event[jsim]=cnt3; 	 

	 }
 
	
	int cdays,cnte;
	cdays = 0;
	
	 for(jsim=year_begin;jsim<year_end-1;jsim++)
{    
	nPer = nyDays[jsim];	
	cdays = cdays+nPer;
	
	if (low_pulse_count[cdays]==1 && low_pulse_count[cdays-1]==1 ){		
		cnte = Event[jsim];
		
		Duration[cnte][jsim] = Duration[cnte][jsim] +Duration[1][jsim+1];

		Event[jsim+1] = Event[jsim+1]-1;
		for (isim=1;isim<=Event[jsim+1];isim++){
		Duration[isim][jsim+1]=Duration[isim+1][jsim+1];}	
	}			
}
	 


	float low_percentile_50th[year_end];
	 
	 	 for(jsim=year_begin;jsim<year_end;jsim++)
{

	for (isim=1;isim<=Event[jsim];isim++){			 
		Daily_FLow_cnt[isim]  = Duration[isim][jsim];
		}

	sort_numbers_ascending(Daily_FLow_cnt,Event[jsim]+1,1);	
	
	
   		st_yr =1;
	    end_yr=Event[jsim]+1;
	    
	    p = 0.5;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    low_percentile_50th[jsim] = Daily_FLow_cnt[pct1]+remain*(Daily_FLow_cnt[pct1+1]-Daily_FLow_cnt[pct1]);       	  	        
        Lopulse_dura[jsim] = low_percentile_50th[jsim];
        Lopulse_event[jsim] = Event[jsim];

}

 	  
// RVA - low pulse count

		sort_numbers_ascending(low_percentile_50th,year_end,year_begin);	
		st_yr =year_begin;
		end_yr=year_end;
	    
	    p = 0.33;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
 
	    pct1=pct1+st_yr-1;
	    *RVA_low_LPD = low_percentile_50th[pct1]+remain*(low_percentile_50th[pct1+1]-low_percentile_50th[pct1]);   
		
		 p = 0.67;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    *RVA_high_LPD = low_percentile_50th[pct1]+remain*(low_percentile_50th[pct1+1]-low_percentile_50th[pct1]);  
		
		 cnt1= 0;
		 cnt2= 0;
	     cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (low_percentile_50th[jsim] <*RVA_low_LPD){
		cnt1=cnt1+1;
	}
	
	if (low_percentile_50th[jsim] >=*RVA_low_LPD && low_percentile_50th[jsim] <=*RVA_high_LPD){
		cnt2=cnt2+1;
	}
 
	if (low_percentile_50th[jsim] >*RVA_high_LPD){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_LPD[0]=cnt1;
	Nexp_LPD[1]=cnt2;
	Nexp_LPD[2]=cnt3; 	
	
//   N expected for events 		     						
	    
	    sort_numbers_ascending(Event,year_end,year_begin);		 
 
	    st_yr =year_begin;
	    end_yr=year_end;	    
	   
	    p = 0.33;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
 
	    pct1=pct1+st_yr-1;
	    *RVA_low_LPE = Event[pct1]+remain*(Event[pct1+1]-Event[pct1]);   
		
		p = 0.67;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    *RVA_high_LPE = Event[pct1]+remain*(Event[pct1+1]-Event[pct1]);  
		
		 cnt1= 0;
		 cnt2= 0;
	     cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
		if (Event[jsim] <*RVA_low_LPE){
			cnt1=cnt1+1;
		}
		
		if (Event[jsim] >=*RVA_low_LPE && Event[jsim] <=*RVA_high_LPE){
			cnt2=cnt2+1;
		}
	 
		if (Event[jsim] >*RVA_high_LPE){
			cnt3=cnt3+1;
		}	
		
	}
	Nexp_LPE[0]=cnt1;
	Nexp_LPE[1]=cnt2;
	Nexp_LPE[2]=cnt3;
   
//***********************************************************   
// High pulse count 
//***********************************************************   
   
   float Event_h[year_end];
   float Duration_h[180][year_end];
   
   cnt1            =0;
   for(jsim=year_begin;jsim<year_end;jsim++)
   {    
	nPer = nyDays[jsim]; 	
	cnt2 = 0;
	cnt3 = 0;
	for(isim=0;isim<nPer;isim++)
	{ 

		 if (high_pulse_count[cnt1]>0)	 
		 {cnt2 = cnt2+1;} 
	 
		 if (high_pulse_count[cnt1]==0)
		 {if (cnt2>0)
		 {cnt3=cnt3+1;		 
		 	Duration_h[cnt3][jsim]=cnt2;
		 }
		 	cnt2 = 0;} 			 			 
			 
		if (high_pulse_count[cnt1]>0 && isim==nPer-1)
		 {cnt3=cnt3+1;
		 Duration_h[cnt3][jsim]=cnt2;
		 }			 		 	 		 									
	     cnt1 = cnt1+1;       
	     
	 }	 
	 Event_h[jsim]=cnt3; 


	 }

//	int cdays,cnte;
	cdays = 0;
	
	 for(jsim=year_begin;jsim<year_end-1;jsim++)
{    
	nPer = nyDays[jsim];	
	cdays = cdays+nPer;
	
	if (high_pulse_count[cdays]==1 && high_pulse_count[cdays-1]==1 ){		
		cnte = Event_h[jsim];

		Duration_h[cnte][jsim] = Duration_h[cnte][jsim] +Duration_h[1][jsim+1];

		Event_h[jsim+1] = Event_h[jsim+1]-1;
		for (isim=1;isim<=Event_h[jsim+1];isim++){
		Duration_h[isim][jsim+1]=Duration_h[isim+1][jsim+1];}	

	}			
}
	 

	float high_percentile_50th[year_end];
	 
	 	 for(jsim=year_begin;jsim<year_end;jsim++)
{

	for (isim=1;isim<=Event_h[jsim];isim++){			 
		Daily_FLow_cnt[isim]  = Duration_h[isim][jsim];
		}

	sort_numbers_ascending(Daily_FLow_cnt,Event_h[jsim]+1,1);	
	 
	    st_yr =1;
	    end_yr=Event_h[jsim]+1;
	    
	    p = 0.5;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    high_percentile_50th[jsim] = Daily_FLow_cnt[pct1]+remain*(Daily_FLow_cnt[pct1+1]-Daily_FLow_cnt[pct1]);       	  	        
        Hipulse_dura[jsim] = high_percentile_50th[jsim];
        Hipulse_event[jsim] = Event_h[jsim];

}

// RVA - high pulse count

	sort_numbers_ascending(high_percentile_50th,year_end,year_begin);
	
	st_yr =year_begin;
	end_yr=year_end;
	    
	    p = 0.33;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
 
	    pct1=pct1+st_yr-1;
	    *RVA_low_HPD = high_percentile_50th[pct1]+remain*(high_percentile_50th[pct1+1]-high_percentile_50th[pct1]);   
		
		 p = 0.67;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    *RVA_high_HPD = high_percentile_50th[pct1]+remain*(high_percentile_50th[pct1+1]-high_percentile_50th[pct1]);  
		
		 cnt1= 0;
		 cnt2= 0;
	     cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (high_percentile_50th[jsim] <*RVA_low_HPD){
		cnt1=cnt1+1;
	}
	
	if (high_percentile_50th[jsim] >=*RVA_low_HPD && high_percentile_50th[jsim] <=*RVA_high_HPD){
		cnt2=cnt2+1;
	}
 
	if (high_percentile_50th[jsim] >*RVA_high_HPD){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_HPD[0]=cnt1;
	Nexp_HPD[1]=cnt2;
	Nexp_HPD[2]=cnt3; 

	///***************************************************************
	
 
//   N expected for events 		     						
	    
	    sort_numbers_ascending(Event_h,year_end,year_begin);		 
 
	    st_yr =year_begin;
	    end_yr=year_end;	    
	   
	    p = 0.33;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
 
	    pct1=pct1+st_yr-1;
	    *RVA_low_HPE = Event_h[pct1]+remain*(Event_h[pct1+1]-Event_h[pct1]);   
		
		p = 0.67;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    *RVA_high_HPE = Event_h[pct1]+remain*(Event_h[pct1+1]-Event_h[pct1]);  
		
		 cnt1= 0;
		 cnt2= 0;
	     cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
		if (Event_h[jsim] <*RVA_low_HPE){
			cnt1=cnt1+1;
		}
		
		if (Event_h[jsim] >=*RVA_low_HPE && Event_h[jsim] <=*RVA_high_HPE){
			cnt2=cnt2+1;
		}
	 
		if (Event_h[jsim] >*RVA_high_HPE){
			cnt3=cnt3+1;
		}	
		
	}
	Nexp_HPE[0]=cnt1;
	Nexp_HPE[1]=cnt2;
	Nexp_HPE[2]=cnt3; 			 
		 
	 
 }
