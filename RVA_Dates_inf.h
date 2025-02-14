void RVA_Dates_inf(int st_yr,int end_yr,float date_min_inf[], float pre_date_min_inf[], float Nexp_date_min[] ){

 	int isim,jsim,ksim,dcnt;	
	int pct1,st_day_pre,end_day_pre, pcti_pre;
	float percentile,remain,pct,pct_pre,remain_pre,percentile_pre;	
	int cnt1,cnt2,cnt3; 	
 	
 	
 	sort_numbers_ascending(date_min_inf,end_yr,st_yr); 	  
			
	float p = 0.5;
	
	pct_pre    = p*(end_yr-st_yr+1);
	pcti_pre   = p*(end_yr-st_yr+1);
	remain_pre = (pct_pre - pcti_pre);
	 
    pcti_pre=pcti_pre+st_yr-1;
	percentile_pre= date_min_inf[pcti_pre]+remain_pre*(date_min_inf[pcti_pre+1]-date_min_inf[pcti_pre]);      
  	pre_date_min_inf[0]=percentile_pre;
  	
  	
  	// common calculation for all indicators
  	
  	p = 0.33;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = date_min_inf[pct1]+remain*(date_min_inf[pct1+1]-date_min_inf[pct1]);      
  	pre_date_min_inf[1]=percentile;	  
	
    p = 0.67;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = date_min_inf[pct1]+remain*(date_min_inf[pct1+1]-date_min_inf[pct1]);      
  	pre_date_min_inf[2]=percentile;  	  	  	 

 	
    cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (date_min_inf[jsim] <pre_date_min_inf[1]){
		cnt1=cnt1+1;
	}
	
	if (date_min_inf[jsim] >=pre_date_min_inf[1] && date_min_inf[jsim] <=pre_date_min_inf[2]){
		cnt2=cnt2+1;
	}

	if (date_min_inf[jsim] >pre_date_min_inf[2]){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_date_min[0]=cnt1;
	Nexp_date_min[1]=cnt2;
	Nexp_date_min[2]=cnt3;	
		
}
