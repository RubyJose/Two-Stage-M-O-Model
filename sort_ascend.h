void sort_numbers_ascending(float number[], int ed, int st){	
	int i,j;
	float temp;
    for (i = st; i < ed; i++)
	{
		for (j = i + 1; j < ed; j++)
		{
			if(number[i] > number[j])
			{
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}		
		}
	}  
}
