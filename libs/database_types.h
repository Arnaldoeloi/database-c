typedef struct{
	char* name;
	char* database;
	char*** data;
}Table;

typedef struct{
	char* name;
	Table* tables;
}Database;
