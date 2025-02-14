
void rates_inf(float Inflow[][366],int st_yr,int end_yr,float* rise_rate_low,float* rise_rate_high,
				float* fall_rate_high,float* fall_rate_low, float Nexp_rise[], float Nexp_fall[],
				float RR_inf[],float FR_inf[])
{

float diff; 
int cnt1,cnt2,cnt3,jsim,nPer,isim;

int nyDays[38]  = {365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365,366,365,365,365};
float rise_rate[366],fall_rate[366];  
float rise_rate_year[38], fall_rate_year[38],rise_rate_med[38], fall_rate_med[38];
 
float p,pct,remain,percentile;
int pct1;


   for(jsim=0;jsim<38;jsim++)
{    
	nPer = nyDays[jsim];
	cnt1 = 0;
	cnt2 = 0;
	
	for(isim=1;isim<nPer;isim++)
	{       		 	 
		diff =  Inflow[jsim][isim]-Inflow[jsim][isim-1];	 		 
		
			if (diff>0) 
			{rise_rate[cnt1] = diff; 			
			 cnt1 =cnt1+1;}
		 
			 if (diff<0)
			 {fall_rate[cnt2] = diff; 
			  cnt2 =cnt2+1;
			 }				  	 	 
	}
		
 
		st_yr= 0;
		end_yr = cnt1;
		sort_numbers_ascending(rise_rate,end_yr,st_yr); 	
 
		p = 0.5;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    float 	percentile = rise_rate[pct1]+remain*(rise_rate[pct1+1]-rise_rate[pct1]);      
	  	
	  	rise_rate_year[jsim] = percentile;
		  RR_inf[jsim] =  rise_rate_year[jsim];
	 
	    st_yr= 0;
		end_yr = cnt2;
		sort_numbers_ascending(fall_rate,end_yr,st_yr); 	
 
		p = 0.5;
		pct    = p*(end_yr-st_yr+1);
		pct1   = p*(end_yr-st_yr+1);
		remain = (pct - pct1);
		 
	    pct1=pct1+st_yr-1;
	    percentile = fall_rate[pct1]+remain*(fall_rate[pct1+1]-fall_rate[pct1]);       	  	
	    fall_rate_year[jsim] = percentile;
	    FR_inf[jsim] = fall_rate_year[jsim];
}

//  rise rate  - median and RVA
		
	    st_yr  = 0;
		end_yr = 38;
		sort_numbers_ascending(rise_rate_year,end_yr,st_yr); 	
 
		 p      = 0.5;
		 pct    = p*(end_yr-st_yr+1);
		 pct1   = p*(end_yr-st_yr+1);
		 remain = (pct - pct1);
		 
	     pct1=pct1+st_yr-1;
         percentile = rise_rate_year[pct1]+remain*(rise_rate_year[pct1+1]-rise_rate_year[pct1]);      
	  	
	  	 *rise_rate_med = percentile; 
	  	 
	  	 p      = 0.33;
		 pct    = p*(end_yr-st_yr+1);
		 pct1   = p*(end_yr-st_yr+1);
		 remain = (pct - pct1);
		 
	     pct1=pct1+st_yr-1;
         percentile = rise_rate_year[pct1]+remain*(rise_rate_year[pct1+1]-rise_rate_year[pct1]);      
	  	
	  	 *rise_rate_low = percentile;
	  	 
	  	 p      = 0.67;
		 pct    = p*(end_yr-st_yr+1);
		 pct1   = p*(end_yr-st_yr+1);
		 remain = (pct - pct1);
		 
	     pct1=pct1+st_yr-1;
         percentile = rise_rate_year[pct1]+remain*(rise_rate_year[pct1+1]-rise_rate_year[pct1]);      
	  	
	  	 *rise_rate_high = percentile;
	  	 
	  	 cnt1= 0;
		 cnt2= 0;
	     cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (rise_rate_year[jsim] <*rise_rate_low){
		cnt1=cnt1+1;
	}
	
	if (rise_rate_year[jsim] >=*rise_rate_low && rise_rate_year[jsim] <=*rise_rate_high){
		cnt2=cnt2+1;
	}

	if (rise_rate_year[jsim] >*rise_rate_high){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_rise[0]=cnt1;
	Nexp_rise[1]=cnt2;
	Nexp_rise[2]=cnt3;
	
// fall rate - median and RVA
 	 
	     st_yr= 0;
		 end_yr = 38;
		 sort_numbers_ascending(fall_rate_year,end_yr,st_yr); 	
 
		  p = 0.5;
		  pct    = p*(end_yr-st_yr+1);
		  pct1   = p*(end_yr-st_yr+1);
		  remain = (pct - pct1);
		 
	      pct1=pct1+st_yr-1;
	      percentile = fall_rate_year[pct1]+remain*(fall_rate_year[pct1+1]-fall_rate_year[pct1]);       	  	
	      *fall_rate_med = percentile;
	      
	      p = 0.33;
		  pct    = p*(end_yr-st_yr+1);
		  pct1   = p*(end_yr-st_yr+1);
		  remain = (pct - pct1);
		 
	      pct1=pct1+st_yr-1;
	      percentile = fall_rate_year[pct1]+remain*(fall_rate_year[pct1+1]-fall_rate_year[pct1]);       	  	
	      *fall_rate_low = percentile;
	      
	      p = 0.67;
		  pct    = p*(end_yr-st_yr+1);
		  pct1   = p*(end_yr-st_yr+1);
		  remain = (pct - pct1);
		 
	      pct1=pct1+st_yr-1;
	      percentile = fall_rate_year[pct1]+remain*(fall_rate_year[pct1+1]-fall_rate_year[pct1]);       	  	
	      *fall_rate_high = percentile;
	      
	      cnt1= 0;
		 cnt2= 0;
	     cnt3= 0;
	
	for(jsim=st_yr;jsim<end_yr;jsim++)
	{
	if (fall_rate_year[jsim] <*fall_rate_low){
		cnt1=cnt1+1;
	}
	
	if (fall_rate_year[jsim] >=*fall_rate_low && fall_rate_year[jsim] <=*fall_rate_high){
		cnt2=cnt2+1;
	}

	if (fall_rate_year[jsim] >*fall_rate_high){
		cnt3=cnt3+1;
	}	
		
	}
	Nexp_fall[0]=cnt1;
	Nexp_fall[1]=cnt2;
	Nexp_fall[2]=cnt3; 
}
	      

