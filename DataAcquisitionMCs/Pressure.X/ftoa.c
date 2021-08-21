void ftoa(float f, unsigned char *array)
	{
    long Byte_High;
	long Byte_Low;

	Byte_High = (long)((float)f);
	Byte_Low = (long)((float)f*1000)-Byte_High*1000;

            //Se guarda cada unidad en una posición de un array
	array[0]   = (Byte_High/100);	//Primero el Byte_High			
	array[1] = (Byte_High/10)-(100*array[0]);
    array[2] = Byte_High-(10*array[1]);

	array[4] = (Byte_Low/100);         //Segundo el Byte_Low
	array[5] = (Byte_Low/10)-(100*array[4]);
    array[6] = Byte_Low-(10*array[5]);
    
	array[7] = '\0'; //Finalizamos el array
	int i=0;
	for(i=0;i<7;i++)
	{
	array[i]=array[i]+48; //pasamos los valores numericos a ASCII
	}
	array[3]=46;  //Numero para representar el caracter '.' en ASCII, colocamos el punto del float

	}
