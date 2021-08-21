void ftoa(float valor, unsigned char *array)
	{
	unsigned char i=0;
    long Byte_High;
	long Byte_Low;

             //Separamos el float,
	Byte_High = (long)((float)valor); //el valor por encima del punto se guarda en Byte_High
	Byte_Low = (long)((float)valor*100)-Byte_High*100; // el valor por debajo del punto se guarda en Byte_Low

            //Se guarda cada unidad en una posición de un array
	array[i]   = (Byte_High/10);	//Primero el Byte_High			
	array[i+1] = Byte_High-(10*array[0]);

	array[i+3] = (Byte_Low/10);         //Segundo el Byte_Low
	array[i+4] = Byte_Low-(10*array[i+3]);
	array[i+5] = '\0'; //Finalizamos el array
	i=0;
	for(i=0;i<5;i++)
	{
	array[i]=array[i]+48; //pasamos los valores numericos a ASCII
	}
	array[2]=46;  //Numero para representar el caracter '.' en ASCII, colocamos el punto del float

	}
