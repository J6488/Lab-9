#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType chain[10];
	int chain_length;
};

// Compute the hash function
int hash(int x)
{
	return x % 10;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i].chain_length > 0) {
			printf("Index %d -> ", i);
			for (int j = 0; j < pHashArray[i].chain_length; j++) {
				printf("%d %c %d", pHashArray[i].chain[j].id, pHashArray[i].chain[j].name, pHashArray[i].chain[j].order);
				if (j != pHashArray[i].chain_length - 1) {
					printf(" -> ");
				}
			}
			printf("\n");
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	int i, hash_size = 10;
	struct HashType *pHashArray = (struct HashType*)malloc(sizeof(struct HashType) * hash_size);
	for (i = 0; i < hash_size; i++) {
		pHashArray[i].chain_length = 0;
	}
	for (i = 0; i < recordSz; i++) {
		int index = hash(pRecords[i].id);
		if (pHashArray[index].chain_length < 10) {
			pHashArray[index].chain[pHashArray[index].chain_length++] = pRecords[i];
		}
	}
	displayRecordsInHash(pHashArray, hash_size);
	free(pRecords);
	free(pHashArray);
}