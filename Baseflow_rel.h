void Baseflow_rel(int st_yr,int end_yr,float daily_relase[][366], float out_seven_daymin[],float base_pre_PCT_Month[],  
					float Nexp_base[] ,float Nobs_base[],float* HA_middle_BF,float BF_outf[] ){
	
	int jsim,isim;
	int nPer;
	int cnt1,cnt2,cnt3;
	float ang_avg,Base_flow_index_out[end_yr];
	int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};

  for(jsim=st_yr;jsim<end_yr;jsim++)
	{		
		
		nPer=nyDays[jsim];
		
		ang_avg = 0.0; 	
					 
		for(isim=0;isim<nPer;isim++)
		{ 		
		ang_avg = ang_avg +  daily_relase[jsim][isim];  		
		}
		
		ang_avg=ang_avg/nPer; 
		
		Base_flow_index_out[jsim] = out_seven_daymin[jsim]/ang_avg;
	    BF_outf[jsim] = Base_flow_index_out[jsim];
	}

// observed number of years falling within the high, middle and low alteration category of RVA 
		
    cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
		if (Base_flow_index_out[jsim] <base_pre_PCT_Month[1]){
			cnt1=cnt1+1;
		}
		
		if (Base_flow_index_out[jsim] >=base_pre_PCT_Month[1] & Base_flow_index_out[jsim] <=base_pre_PCT_Month[2]){
			cnt2=cnt2+1;
			
		}
	
		if (Base_flow_index_out[jsim] >base_pre_PCT_Month[2]){
			cnt3=cnt3+1;
		}	
		
	}
	

	Nobs_base[0]=cnt1;
	Nobs_base[1]=cnt2;
	Nobs_base[2]=cnt3;
 
 //HA_low[0]    = fabs((Nobs_Month[0]-Nexp_Month[0])/Nexp_Month[0])*100;	
 *HA_middle_BF   = fabs((Nobs_base[1]-Nexp_base[1])/Nexp_base[1])*100;	
 //HA_high[0]   = fabs((Nobs_Month[2]-Nexp_Month[2])/Nexp_Month[2])*100;
}
