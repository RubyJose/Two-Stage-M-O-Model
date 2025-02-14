void Baseflow_inf(int st_yr,int end_yr,float daily_inflow[][366], float inf_seven_daymin[],float base_pre_PCT_Month[],  
					float Nexp_base[],float BF_inf[] ){

	int jsim,isim;
	int nPer;
	float ang_avg;
	float Base_flow_index[end_yr]; 
	int pct1,st_d,end_d, pcti_pre;
	float percentile,remain,pct,pct_pre,remain_pre,percentile_pre;
    int cnt1,cnt2,cnt3; 
    int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};
    
	    
	for(jsim=st_yr;jsim<end_yr;jsim++)
	
	{		
	
		nPer=nyDays[jsim];
		
		ang_avg = 0.0; 	
	 
		for(isim=0;isim<nPer;isim++)
		{ 		
		ang_avg = ang_avg + daily_inflow[jsim][isim];  		
		}
		
		ang_avg=ang_avg/nPer;
				
		Base_flow_index[jsim] = inf_seven_daymin[jsim]/ang_avg;
		BF_inf[jsim] = Base_flow_index[jsim] ;
	}
	

	sort_numbers_ascending(Base_flow_index,end_yr,st_yr); 
	
	float p = 0.5;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = Base_flow_index[pct1]+remain*(Base_flow_index[pct1+1]-Base_flow_index[pct1]);      
  
  	base_pre_PCT_Month[0]=percentile;
	 
// RVA boundaries 
  	 
	p = 0.33;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = Base_flow_index[pct1]+remain*(Base_flow_index[pct1+1]-Base_flow_index[pct1]);      
  
  	base_pre_PCT_Month[1]=percentile;	  
	
    p = 0.67;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = Base_flow_index[pct1]+remain*(Base_flow_index[pct1+1]-Base_flow_index[pct1]);      
    
  	base_pre_PCT_Month[2]=percentile;
	
// expected number of years falling within the high, middle and low alteration category of RVA 

	cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (Base_flow_index[jsim] <base_pre_PCT_Month[1]){
		cnt1=cnt1+1;
	}
	
	if (Base_flow_index[jsim] >=base_pre_PCT_Month[1] && Base_flow_index[jsim] <=base_pre_PCT_Month[2]){
		cnt2=cnt2+1;
	}

	if (Base_flow_index[jsim] >base_pre_PCT_Month[2]){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_base[0]=cnt1;
	Nexp_base[1]=cnt2;
	Nexp_base[2]=cnt3;	
}
