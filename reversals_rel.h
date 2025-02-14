void Reversals_rel(int st_yr,int end_yr,float Outflow[][366], float pre_PCT_reversals[3], 
float Nexp_reversals[3],float Nobs_reversals[3],float* HA_middle_reversal,float Reversal_outf[]){


int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};
int dcnt, reversals, jsim;
float diff,year_diff[366],reversal_Outflow[38];

float pct,remain,percentile,post_PCT_reversals;
int   pct1,st_d,end_d;


int nPer,isim;
float cnt1,cnt2,cnt3;
	 
	
	for (jsim=st_yr;jsim<end_yr;jsim++)
	{
		dcnt = 0;
		nPer = nyDays[jsim]-1;
	
		for (isim=0;isim<nPer;isim++)
		{
			diff = Outflow[jsim][isim]-Outflow[jsim][isim+1];
			if (fabs(diff)>0){
				year_diff[dcnt] = diff;
				dcnt = dcnt+1;				
			}				
		}
					reversals = 0;
		
		for (isim=0;isim<dcnt-1;isim++)
		{
	
			if (year_diff[isim]*year_diff[isim+1]<0){
				reversals = reversals+1;				
			}				
		}
		reversal_Outflow[jsim] =  reversals;	
		Reversal_outf[jsim] = reversal_Outflow[jsim];				
	}

	
		sort_numbers_ascending(reversal_Outflow,end_yr,st_yr); 
					 	 
	    float p = 0.5;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
		percentile = reversal_Outflow[pct1]+remain*(reversal_Outflow[pct1+1]-reversal_Outflow[pct1]);      
		post_PCT_reversals=percentile;
	
		
//count of Nexp

    cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (reversal_Outflow[jsim] < pre_PCT_reversals[2]){
		cnt1=cnt1+1;
	}
	
	if (reversal_Outflow[jsim] >=	pre_PCT_reversals[2] && reversal_Outflow[jsim] <=	pre_PCT_reversals[3]){
		cnt2=cnt2+1;
	}

	if (reversal_Outflow[jsim]>	pre_PCT_reversals[3]){
		cnt3=cnt3+1;
	}	
		
	}
	Nobs_reversals[0]=cnt1;
	Nobs_reversals[1]=cnt2;
	Nobs_reversals[2]=cnt3;
	
	
	//HA_low_rise   = (Nobs_rise[0]-Nexp_rise[0])/Nexp_rise[0];	
 *HA_middle_reversal   = fabs((Nobs_reversals[1]-Nexp_reversals[1])/Nexp_reversals[1])*100;	
 //HA_high_rise    = (Nobs_rise[2]-Nexp_rise[2])/Nexp_rise[2];	      

}
