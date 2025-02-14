void reservoir_operation(int isim, int jsim,double WA[][38],double EfRelTar[][38],double IrrRelTar[][38],double CoStTar[],
						double EfRel[][38],double IrrRel[][38],double EfTar[][38],double IrrTar[],
						 double CoSt[][38],double Spil[][38]) 
{
	double IrrRelDef[12][38],ExcessWA[12][38], EfRelDef[12][38];			
				
				if (WA[isim][jsim] >= EfTar[isim][jsim]+IrrTar[isim]+CoStTar[isim])
				{
					
					EfRel[isim][jsim]  = EfTar[isim][jsim];
					IrrRel[isim][jsim] = IrrTar[isim];
					CoSt[isim][jsim] = CoStTar[isim];
					Spil[isim][jsim] = WA[isim][jsim] - EfTar[isim][jsim] - IrrTar[isim] - CoStTar[isim];
				}
				else if (WA[isim][jsim] >= EfRelTar[isim][jsim]+IrrRelTar[isim][jsim]+CoStTar[isim])			//	hedged targets 
				{
					EfRel[isim][jsim]  = EfRelTar[isim][jsim];
					IrrRel[isim][jsim] = IrrRelTar[isim][jsim];					
					CoSt[isim][jsim] = CoStTar[isim];
					Spil[isim][jsim] = 0;
					
					
					IrrRelDef[isim][jsim] = IrrTar[isim] - IrrRel[isim][jsim];
					EfRelDef[isim][jsim]  = EfTar[isim][jsim]  - EfRel[isim][jsim];
					ExcessWA[isim][jsim]  = WA[isim][jsim]  - EfRelTar[isim][jsim] - IrrRelTar[isim][jsim] - CoStTar[isim];
					
					
					if (ExcessWA[isim][jsim] >= EfRelDef[isim][jsim]+IrrRelDef[isim][jsim])
					{
						EfRel[isim][jsim]  = EfTar[isim][jsim];
						IrrRel[isim][jsim] = IrrTar[isim];
					}
					else if (ExcessWA[isim][jsim] >= EfRelDef[isim][jsim])
					{
						EfRel[isim][jsim]  = EfTar[isim][jsim];
						IrrRel[isim][jsim] = IrrRel[isim][jsim] + ExcessWA[isim][jsim] - EfRelDef[isim][jsim];
					}
					else if (ExcessWA[isim][jsim] >= 0)
					{
						EfRel[isim][jsim] = EfRel[isim][jsim] + ExcessWA[isim][jsim];
					}
				}
				else if (WA[isim][jsim] >= EfRelTar[isim][jsim]+IrrRelTar[isim][jsim])
				{
				
					EfRel[isim][jsim]  = EfRelTar[isim][jsim];
					IrrRel[isim][jsim] = IrrRelTar[isim][jsim];
					CoSt[isim][jsim] = WA[isim][jsim]  - EfRelTar[isim][jsim] - IrrRelTar[isim][jsim] ;
					Spil[isim][jsim] = 0;
				}
			
				else if (WA[isim][jsim] >= EfRelTar[isim][jsim])
				{
					
					IrrRel[isim][jsim] = WA[isim][jsim]  - EfRelTar[isim][jsim];
					EfRel[isim][jsim]  = EfRelTar[isim][jsim];
					CoSt[isim][jsim] = 0;
					Spil[isim][jsim] = 0;
				}
				else if (WA[isim][jsim] >= 0)
				{
				
					IrrRel[isim][jsim] = 0;
					EfRel[isim][jsim]  = WA[isim][jsim];
					CoSt[isim][jsim] = 0;
					Spil[isim][jsim] = 0;
				}
				else if (WA[isim][jsim] < 0)
				{
				
					IrrRel[isim][jsim] = 0;
					EfRel[isim][jsim]  = 0;
					CoSt[isim][jsim] = WA[isim][jsim];
					Spil[isim][jsim] = 0;
				}
			
			
}
