
void IHA_median_rel(int st_yr,int end_yr,int nYear, float Release[][366], float pre_PCT_Month[][3], float Nexp_Month[][3],
						float Nobs_Month[][3],float HA_middle[],float Median_Year[][12]){

// Monthly no. of Days
 
int nDays[12]   = {30, 31, 31, 30, 31, 30, 31,31, 28, 31, 30, 31};
int ncdays[13]  = {0,30,61,92,122,153,183,214,245,273,304,334,365};
int ncldays[13] = {0,30,61,92,122,153,183,214,245,274,305,335,366};
int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};
	
int jsim,isim;
int ksim,nPer;

float cnt1,cnt2,cnt3;


float year_flow[366],post_PCT_Month[12][3];
float Median_Monthly[38];

// median yearwise 
float pct,remain,percentile;
float month_flow[366];
int   pct1,st_d,end_d;
//**************************************************************************************


for(jsim=0;jsim<nYear;jsim++)
{    
	nPer = nyDays[jsim];
	
	for(isim=0;isim<12;isim++)
	{    	
		st_d  = ncdays[isim];
		end_d = ncdays[isim+1];
		
		if(nPer>365 & isim>0 )
		{	st_d  = ncldays[isim];
			end_d = ncldays[isim+1];
		}	
		

	 	for(ksim=st_d;ksim<end_d;ksim++) 
	 	{
		 month_flow[ksim] =  Release[jsim][ksim];	 		 
		 }	
	 
		sort_numbers_ascending(month_flow,end_d,st_d); 
					 	 
	    float p = 0.5;
		pct    = p*(end_d-st_d+1);
		pct1   = p*(end_d-st_d+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_d-1;
		percentile = month_flow[pct1]+remain*(month_flow[pct1+1]-month_flow[pct1]);      
		Median_Year[jsim][isim]=percentile;
		
	}   	 
}

//**************************************************************************************
 

//**************************************************************************************
 

// post-impact - percentiles
for(isim=0;isim<12;isim++)
{	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{ 
	Median_Monthly[jsim]=Median_Year[jsim][isim];
	}  	 
	  sort_numbers_ascending(Median_Monthly,end_yr,st_yr);  
	  
 
	float p = 0.5;
	pct    = p*(end_yr-st_yr+1);
	pct1   = p*(end_yr-st_yr+1);
	remain = (pct - pct1);
	 
    pct1=pct1+st_yr-1;
	percentile = Median_Monthly[pct1]+remain*(Median_Monthly[pct1+1]-Median_Monthly[pct1]);      
  	post_PCT_Month[isim][0]=percentile;
	  	 
}

//count of Nobs
	
for(isim=0;isim<12;isim++){	
    cnt1= 0;
	cnt2= 0;
	cnt3= 0;
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
		if (Median_Year[jsim][isim] <pre_PCT_Month[isim][1]){
			cnt1=cnt1+1;
		}
		
		if (Median_Year[jsim][isim] >=pre_PCT_Month[isim][1] && Median_Year[jsim][isim] <=pre_PCT_Month[isim][2]){
			cnt2=cnt2+1;
		}
	
		if (Median_Year[jsim][isim] >pre_PCT_Month[isim][2]){
			cnt3=cnt3+1;
		}	
		
	}
	Nobs_Month[isim][0]=cnt1;
	Nobs_Month[isim][1]=cnt2;
	Nobs_Month[isim][2]=cnt3;

}

for(isim=0;isim<12;isim++){
 
 //HA_low[isim] = (Nobs_Month[isim][1]-Nexp_Month[isim][1])/Nexp_Month[isim][1];	
 HA_middle[isim] = fabs((Nobs_Month[isim][1]-Nexp_Month[isim][1])/Nexp_Month[isim][1])*100;	
 //HA_high[isim] = (Nobs_Month[isim][3]-Nexp_Month[isim][3])/Nexp_Month[isim][3];	  
 
}
	
}

