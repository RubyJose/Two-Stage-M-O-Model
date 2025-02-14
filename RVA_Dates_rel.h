void RVA_Dates_rel(int st_yr,int end_yr,float date_min_rel[], float pre_date_min_inf[],
float pre_date_min_rel[], float Nexp_date_min[], float Nobs_date_min[], float* HA_middle ){

 	int isim,jsim,ksim,dcnt;	
	int pct1,st_day_pre,end_day_pre, pcti_pre;
	float percentile,remain,pct,pct_pre,remain_pre,percentile_pre;	
	int cnt1,cnt2,cnt3; 
				
 	
 	sort_numbers_ascending(date_min_rel,end_yr,st_yr); 	  
			
	float p = 0.5;
	
	pct_pre    = p*(end_yr-st_yr+1);
	pcti_pre   = p*(end_yr-st_yr+1);
	remain_pre = (pct_pre - pcti_pre);
	 
    pcti_pre=pcti_pre+st_yr-1;
	percentile_pre= date_min_rel[pcti_pre]+remain_pre*(date_min_rel[pcti_pre+1]-date_min_rel[pcti_pre]);      
  	pre_date_min_rel[0]=percentile_pre;
  	
  	  	
    cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (date_min_rel[jsim] <pre_date_min_inf[1]){
		cnt1=cnt1+1;
	}
	
	if (date_min_rel[jsim] >=pre_date_min_inf[1] && date_min_rel[jsim] <=pre_date_min_inf[2]){
		cnt2=cnt2+1;
	}

	if (date_min_rel[jsim] >pre_date_min_inf[2]){
		cnt3=cnt3+1;
	}	
		
	}
	Nobs_date_min[0]=cnt1;
	Nobs_date_min[1]=cnt2;
	Nobs_date_min[2]=cnt3;	
	
	
	*HA_middle   = fabs((Nobs_date_min[1]-Nexp_date_min[1])/Nexp_date_min[1])*100;
		
}
