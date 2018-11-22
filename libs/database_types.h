typedef struct{
	char* name;
	char* database;
	int numRows;
	int numCols;
	char*** data;
}Table;

typedef struct{
	char* name;
	Table* tables;
}Database;

typedef struct{
	char* typeOfFilter;
	char* column;
	char* value;
}Filter;
