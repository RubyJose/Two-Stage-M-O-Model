void Extremities_inf(float min_max, int st_yr,int end_yr,int x_day,float Inflow[][366], float pre_xday_min[],  
						float Nexp_Month[],float xday_min_inf[] ){


int nDays[12]   = {30, 31, 31, 30, 31, 30, 31,31, 28, 31, 30, 31};
int ncdays[13]  = {0,30,61,92,122,153,183,214,245,273,304,334,365};
int ncldays[13] = {0,30,61,92,122,153,183,214,245,274,305,335,366};
int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};

int isim,jsim,ksim,nPer;

int pct1,st_day_pre,end_day_pre, pcti_pre;
float percentile,remain,pct,pct_pre,remain_pre,percentile_pre;

float x_sum, x_min, x_max, x_run_sum[92][366];

int cnt1,cnt2,cnt3; 
float post_xday_min[1],x_daymin[366], x_daymax[366];
	
for(jsim=st_yr;jsim<end_yr;jsim++){ 
  
  nPer    = nyDays[jsim]-(x_day-1); 
  
  for(isim=0;isim<nPer;isim++)	
	{ 
	    x_sum = 0.0;
		for (ksim=0+isim;ksim<x_day+isim;ksim++)
		{x_sum = x_sum+Inflow[jsim][ksim];	 
						
		}		
		x_sum=x_sum/x_day;
		x_run_sum[jsim][isim] = x_sum;
	}
}

// maximum and minimum 

for(jsim=st_yr;jsim<end_yr;jsim++){ 
  nPer    = nyDays[jsim]-(x_day-1); 
  
  x_min  = 2540000.0; 
  x_max  = 0.0; 
  
  for(isim=0;isim<nPer;isim++)
	{		
		if (x_run_sum[jsim][isim]<x_min)
			{x_min = x_run_sum[jsim][isim];}  
			
		if (x_run_sum[jsim][isim]>x_max)
			{x_max = x_run_sum[jsim][isim];}  	     
	}	
	x_daymin[jsim] = x_min; 
	x_daymax[jsim] = x_max;  
}

	
	if (min_max<0){
		for(jsim=st_yr;jsim<end_yr;jsim++)
	{ 
	x_daymin[jsim] = x_daymax[jsim];
	}
			
	}

//  percentiles - x-days min

	for(jsim=st_yr;jsim<end_yr;jsim++)
	{ 
	xday_min_inf[jsim] = x_daymin[jsim];
	x_daymin[jsim] = x_daymin[jsim];	
	}
	
	  sort_numbers_ascending(x_daymin,end_yr,st_yr); 	  
			
	float p = 0.5;
	
	pct_pre    = p*(end_yr-st_yr+1);
	pcti_pre   = p*(end_yr-st_yr+1);
	remain_pre = (pct_pre - pcti_pre);
	 
    pcti_pre=pcti_pre+st_yr-1;
	percentile_pre= x_daymin[pcti_pre]+remain_pre*(x_daymin[pcti_pre+1]-x_daymin[pcti_pre]);      
  	pre_xday_min[0]=percentile_pre;
  	
  	
// common calculation for all indicators
  	
  	p = 0.33;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = x_daymin[pct1]+remain*(x_daymin[pct1+1]-x_daymin[pct1]);      
  	pre_xday_min[1]=percentile;	  
	
    p = 0.67;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = x_daymin[pct1]+remain*(x_daymin[pct1+1]-x_daymin[pct1]);      
  	pre_xday_min[2]=percentile;  	  	  	 

// Expected number of years falling within low, middle and high alteration category
 	
    cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (x_daymin[jsim] <pre_xday_min[1]){
		cnt1=cnt1+1;
	}
	
	if (x_daymin[jsim] >=pre_xday_min[1] && x_daymin[jsim] <=pre_xday_min[2]){
		cnt2=cnt2+1;
	}

	if (x_daymin[jsim] >pre_xday_min[2]){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_Month[0]=cnt1;
	Nexp_Month[1]=cnt2;
	Nexp_Month[2]=cnt3;
  	   
}
