void HCA_Dec( int nYear,int nPer,float Preimpact[][38], float Postimpact[][38],
				float* sqr_DCM) {

	float yearly_inflow[nYear],yearly_rel[nYear];
	float first_yearly[nYear/2],second_yearly[nYear/2];
	float rC,ncm[nYear],ncm1[nYear],class_width[nYear];
	
	int   pct1,st_d,end_d;
	float pct,remain,percentile,p,Q1,Q3,RQ;	
	float Monthly_max[nYear],Monthly_min[nYear];
	int max_cond;
	int isim,jsim,ksim,dcnt;
	float Sm[12],DCm[12];
	int loop_start,loop_end;
	loop_start = 6; 
	loop_end = 7; 
	

 	for(isim=loop_start;isim<loop_end;isim++) 
    {		
		for(jsim=0;jsim<nYear;jsim++)
		{		
			yearly_inflow[jsim] = Preimpact[isim][jsim];			
			yearly_rel[jsim]    = Postimpact[isim][jsim];				

		}
	
						
 		sort_numbers_ascending(yearly_inflow,nYear,0);
     	sort_numbers_ascending(yearly_rel,nYear,0);
     	
		 rC = yearly_inflow[nYear-1]	- yearly_inflow[0];
		 
		 	 
		  Monthly_min[isim] = yearly_inflow[0];
		  Monthly_max[isim] = yearly_inflow[nYear-1];
		  
//	printf("%f\t%f\n",Monthly_min[isim],Monthly_max[isim]);	 	
			
		for(jsim=0;jsim<nYear/2;jsim++)
		{		 
		 first_yearly[jsim]=yearly_inflow[jsim] ;
		}
			 	
	 	end_d = nYear/2;
		st_d  = 0; 
	   		 	     		 	
        p = 0.5;
		pct    = p*(end_d-st_d+1);
		pct1   = p*(end_d-st_d+1);
		remain = (pct - pct1);		 
	    pct1   = pct1+st_d-1;
		Q1     = first_yearly[pct1]+remain*(first_yearly[pct1+1]-first_yearly[pct1]);      
	 		
	//	printf("%i %i\n",nYear/2+1,nYear/2);
		
		
		
		dcnt=0;
		for(jsim=nYear/2;jsim<nYear;jsim++)
		{	second_yearly[dcnt]=yearly_inflow[jsim] ;
			
			dcnt=dcnt+1;
		}			
	
        end_d = nYear/2;
		st_d  = 0; 
	   		 	     		 	
        p = 0.5;
		pct    = p*(end_d-st_d+1);
		pct1   = p*(end_d-st_d+1);
		remain = (pct - pct1);		 
	    pct1   = pct1+st_d-1;
		Q3     = second_yearly[pct1]+remain*(second_yearly[pct1+1]-second_yearly[pct1]);      
	 
	  	// printf("Quartiles,%f\t%f\n",	Q1   ,	Q3   );
	  	 
	    RQ     = Q3-Q1;
	    
	   
	   ncm[isim]=ceil(rC*pow(nYear,(1.0/3.0))/(2.0*RQ));
	  // ncm[isim]  = sqrt(nYear);	  
	    //ncm[isim]   = ceil(1+3.3*log10(nYear));
	    ncm1[isim] =  ncm[isim];	    		    
	    class_width[isim] = rC/ncm[isim];
		
	//	printf("%f\n",ncm[isim]);
		
	//	printf(" quartile values %f\t %f\t%f\t%f\n",Q1,Q3,ncm[isim],class_width[isim]);
		  				   	 									
   }	
	   
	   
	sort_numbers_ascending(ncm1,nPer,0);		 	 	
	max_cond = ncm1[nPer-1]+1;			 
	 
	float range_month[nPer][max_cond]; 
			 
			 			 		
	 		
	for(isim=loop_start;isim<loop_end;isim++) 		 	
	    {
	    	
	    	range_month[isim][0]=0;	    	
	    	
			for(jsim=1;jsim<ncm[isim];jsim++)
			{				
			range_month[isim][jsim]=range_month[isim][jsim-1]+class_width[isim];
			}

						
			for(jsim=ncm[isim];jsim<ncm[isim]+1;jsim++)
			{				
			range_month[isim][jsim]=Monthly_max[isim]+1.01;								
			}
		
		}		
		
	float mnflow,mnrel; 
	float cnt,cnt1 ; 
	float freq_inflow[nPer][max_cond],rel_freq_inflow[nPer][max_cond];
	
		 			
	for(isim=loop_start;isim<loop_end;isim++)		 	
	    {  
	    	for(ksim=0;ksim<ncm[isim];ksim++)
			{	
			    cnt = 0;
				cnt1 = 0;			
				
				for(jsim=0;jsim<nYear;jsim++)
				{ 					
					mnflow = Preimpact[isim][jsim];				
				    if (mnflow>=range_month[isim][ksim] && mnflow<range_month[isim][ksim+1])
				    {				    	
				    	cnt=cnt+1; 	
					}
																															
				}
			
		
				
// Frequency vector 
				freq_inflow[isim][ksim]=cnt;
				rel_freq_inflow[isim][ksim]=cnt/nYear;	
				
			//	printf("%f,%f \n",cnt,rel_freq_inflow[isim][ksim]);									 					
			}
		// printf("============================\n" );	
				
			//system("pause"); 
		}
		
		
	float freq_rel[nPer][max_cond],rel_freq_release[nPer][max_cond];
	 	
	for(isim=loop_start;isim<loop_end;isim++)	 	
	    {  
	    	for(ksim=0;ksim<ncm[isim];ksim++)
			{		     
				cnt1 = 0;			
				
				for(jsim=0;jsim<nYear;jsim++)
				{ 					
				dcnt=ncm[isim];												
				
				mnrel = Postimpact[isim][jsim];	
				
	//printf("%f \t %f \t %f\n", mnrel,range_month[isim][ksim],range_month[isim][ksim+1]);
							
			    if (mnrel>=range_month[isim][ksim] && mnrel<range_month[isim][ksim+1])
			    	{				    	
			    	cnt1=cnt1+1; 
			    	}
			
			 if (mnrel>=range_month[isim][dcnt] &&  ksim== dcnt-1)
					{
					cnt1=cnt1+1;
					}																				
				}
				
				freq_rel[isim][ksim]=cnt1;
				rel_freq_release[isim][ksim]=cnt1/nYear;	
				
			//	printf("%f\t%f  \n",cnt1,rel_freq_release[isim][ksim]);	
								
			}
		//	system("pause")	;
		//	printf("========================\n");
		//	printf("============================\n" );			
		}
				
		float rank_inflow[nPer][max_cond];
		float rank_outflow[nPer][max_cond];
		float freq_inf[max_cond],sorted_freq_inf[max_cond],uniq_freq_inf[max_cond];		
		float freq_outflow[max_cond],sorted_freq_outflow[max_cond];		
		float monthly_rel_freq_inf[nPer][max_cond],monthly_rel_freq_rel[nPer][max_cond];		
		float seriel_inflow[nPer][max_cond],seriel_outflow[nPer][max_cond];   
		int   cnt_f,cnt_r,dcnt_L; 
			int msim; 
		
		//float check_freq_inf[3] = {0.105263158,0.473684211,0.421052632};		
		
// Ranking the relative frequency 

		
 
// Inflow ************************************************************** 
			
		for(isim=loop_start;isim<loop_end;isim++) 		 	
	    {  
	    	dcnt=ncm[isim];
	    	for(ksim=0;ksim<dcnt;ksim++)
			{
			 freq_inf[ksim]         = rel_freq_inflow[isim][ksim];
			 sorted_freq_inf [ksim] = freq_inf[ksim]; 			  			 
			}
			
			int i,j;
			float temp;
		    for (i = 0; i < dcnt; i++)
			{
				for (j = i + 1; j < dcnt; j++)
				{
					if(sorted_freq_inf[i] < sorted_freq_inf[j])
					{
						temp = sorted_freq_inf[i];
						sorted_freq_inf[i] = sorted_freq_inf[j];
						sorted_freq_inf[j] = temp;
					}		
				}
			}  
				
			msim = 0;
			 for (i = 0; i < dcnt; i++)
			{
				
			if (i>0 & sorted_freq_inf[i]==sorted_freq_inf[i-1]){
				}
			else {
		
					for (j = 0; j < dcnt; j++)
					{						
					if(sorted_freq_inf[i] == freq_inf[j])
						{
						seriel_inflow[isim][msim] = j+1;
						
						//	printf("%i series number Inflow,%f\n ",j+1,freq_inf[j]);
						msim=msim+1;	
						}						
					}			

				}					
			monthly_rel_freq_inf[isim][i]=sorted_freq_inf[i];
			//	printf("%f\n",monthly_rel_freq_inf[isim][i]);	
			}													 				 	
		}
			
		 //	system("pause");
										
 
// Outflow ************************************************************** 

	for(isim=loop_start;isim<loop_end;isim++) 		 	
	    {  
	    	dcnt=ncm[isim];
	    	for(ksim=0;ksim<dcnt;ksim++)
			{			 
			 freq_outflow[ksim]         = rel_freq_release[isim][ksim];
			 sorted_freq_outflow[ksim]  = freq_outflow[ksim]; 			 
			}
			
			int i,j;
			float temp;
		    for (i = 0; i < dcnt; i++)
			{
				for (j = i + 1; j < dcnt; j++)
				{
					if(sorted_freq_outflow[i] < sorted_freq_outflow[j])
					{
						temp = sorted_freq_outflow[i];
						sorted_freq_outflow[i] = sorted_freq_outflow[j];
						sorted_freq_outflow[j] = temp;
					}		
				}
			}  
				
			msim = 0;
			 for (i = 0; i < dcnt; i++)
			{
				
			if (i>0 & sorted_freq_outflow[i]==sorted_freq_outflow[i-1]){
				}
			else {
		
					for (j = 0; j < dcnt; j++)
					{						
					if(sorted_freq_outflow[i] == freq_outflow[j])
						{
						seriel_outflow[isim][msim] = j+1;
						
					//	printf("%i series number outflow,%f\n ",j+1,freq_outflow[j]);
						
						msim=msim+1;	
						}						
					}			

				}								
			monthly_rel_freq_rel[isim][i] =  sorted_freq_outflow[i];
			
		//	printf("%f\n",monthly_rel_freq_rel[isim][i]);	
			}													 				 	
		}


	float  s1_min_value,sum_min,Monthly_S1[nPer],Monthly_S2[nPer]; 
	float  s2_min_value,coeff,S2,sqr1_DCM; 
	 	
	 	
	 	sqr1_DCM = 0;
		for(isim=loop_start;isim<loop_end;isim++) 		 	
	    {  
	    	dcnt=ncm[isim];
	    	sum_min = 0; 
	    	S2      = 0; 	    	
	    	for(ksim=0;ksim<dcnt;ksim++)
			{			
				if (rel_freq_inflow[isim][ksim]<rel_freq_release[isim][ksim]){				
					s1_min_value = rel_freq_inflow[isim][ksim]; 								
				}
				else {
					s1_min_value = rel_freq_release[isim][ksim]; 								
				}
				
											
 			
			 	sum_min =  sum_min + s1_min_value;	
				 
				 			 
			 	
			    if (monthly_rel_freq_inf[isim][ksim]<monthly_rel_freq_rel[isim][ksim]){				
					s2_min_value = monthly_rel_freq_inf[isim][ksim]; 								
				}
				else {
					s2_min_value = monthly_rel_freq_rel[isim][ksim]; 								
				}				
				
				
				
				coeff = 1.0-(fabs(seriel_inflow[isim][ksim]- seriel_outflow[isim][ksim])/ncm[isim])	;
						 			 			 			 			 			 			 			 
			    S2 =  S2+ s2_min_value*coeff; 
			    
			    	//	printf("July S2 %f\n",S2)	;
	//		    
	  	 //printf("%f\t\n",coeff); 	 
			    
		}			
			
		//	printf("============================================\n");
			
			
			
			Monthly_S1[isim] = sum_min; 
			Monthly_S2[isim] = S2 ; 
			
			
			//  system("pause");
			
		//	printf("June %f\t %f\n",Monthly_S1[isim],Monthly_S2[isim] ); 
			
			Sm[isim] = sqrt(Monthly_S1[isim] *Monthly_S2[isim]); 									
			DCm[isim] = (1.0-Sm[isim])*100.0; 

	 //	printf("%f\t %f\n",Sm[isim],DCm[isim] );
		
		sqr1_DCM = sqr1_DCM +DCm[isim]*DCm[isim];
//		sqr1_DCM = DCm[isim]*DCm[isim];
		
	 //	printf("%f\t%f\t%f\n",Sm[isim],DCm[isim],sqr1_DCM );	
		}
		
		*sqr_DCM=sqr1_DCM;
			
	}
