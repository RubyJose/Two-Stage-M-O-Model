void Reversals_inf(int st_yr,int end_yr,float Inflow[][366], float pre_PCT_reversals[3], float Nexp_reversals[3],
					float Reversal_inf[]){


int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};
int dcnt, reversals, jsim;
float diff,year_diff[366],reversal_inflow[38];

float pct,remain,percentile;
int   pct1,st_d,end_d;

int nPer,isim;
float cnt1,cnt2,cnt3;
	 
	
	for (jsim=st_yr;jsim<end_yr;jsim++)
	{
		dcnt = 0;
		nPer = nyDays[jsim]-1;
	
		for (isim=0;isim<nPer;isim++)
		{
			diff = Inflow[jsim][isim]-Inflow[jsim][isim+1];
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
		reversal_inflow[jsim] =  reversals;	
		Reversal_inf [jsim] = 	reversal_inflow[jsim];			
	}

	
		sort_numbers_ascending(reversal_inflow,end_yr,st_yr); 
					 	 
	    float p = 0.5;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
		percentile = reversal_inflow[pct1]+remain*(reversal_inflow[pct1+1]-reversal_inflow[pct1]);      
		pre_PCT_reversals[1]=percentile;
		
		p = 0.33;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
		percentile = reversal_inflow[pct1]+remain*(reversal_inflow[pct1+1]-reversal_inflow[pct1]);      
		pre_PCT_reversals[2]=percentile;
		
		p = 0.67;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
		percentile = reversal_inflow[pct1]+remain*(reversal_inflow[pct1+1]-reversal_inflow[pct1]);      
		pre_PCT_reversals[3]=percentile;
		
//count of Nexp

    cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (reversal_inflow[jsim] <	pre_PCT_reversals[2]){
		cnt1=cnt1+1;
	}
	
	if (reversal_inflow[jsim] >=	pre_PCT_reversals[2] && reversal_inflow[jsim] <=	pre_PCT_reversals[3]){
		cnt2=cnt2+1;
	}

	if (reversal_inflow[jsim]>	pre_PCT_reversals[3]){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_reversals[0]=cnt1;
	Nexp_reversals[1]=cnt2;
	Nexp_reversals[2]=cnt3;
	
}
