#include "PatriciaTree.h"
#include "PatriciaNode.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

typedef struct {
	char *key;
	char *path;
	unsigned long long val;
} Item;

enum Token {
	Exit,
	Insert,
	Remove,
	Search,
	Save,
	Load,
	Error,
	Skip
};

void Tolower(char * th)
{
	int len = strlen(th);
	for (int i = 0; i < len; i++) {
		th[i] = tolower(th[i]);
	}
}

Token ReadLine(FILE *f, Item *th)
{
	//if (th->path) delete [] th->path;
	char arg1[5];
	arg1[4] = '\0';
	int len = 256;

	char c = getchar();
	Token result;


	if (c == EOF) {
		return Exit;
	} else if (c == '\n' || c == ' ') {
		return  Skip;
	}
	c = tolower(c);

	if (c == '+') {
		//th->key = NULL;
		//th->key = new char[len + 1];
		memset (th->key, '\0', len + 1);

		fscanf(f, "%s", th->key);
		Tolower(th->key);
		fscanf(f, "%llu", &(th->val));
		result = Insert;

	} else if (c == '-') {
		//th->key = NULL;
		//th->key = new char[len + 1];
		memset (th->key, '\0', len + 1);

		fscanf(f, "%s", th->key);
		Tolower(th->key);

		result = Remove;

	} else if (c == '!') {
		fscanf(f, "%s", arg1);
		memset (th->path, '\0', len + 1);

		fscanf(f, "%s", th->path);

		if (!strcmp(arg1, "Save")) {
			result = Save;
		} else if (!strcmp(arg1, "Load")) {
			result = Load;
		} else {
			result = Error;
		}

	} else {
		if (isalnum(c))
		     ungetc(c, f);
		//th->key = NULL;
		//th->key = new char[len + 1];
		memset (th->key, '\0', len + 1);

		fscanf(f, "%s", th->key);
		Tolower(th->key);
		result = Search;
	}
	return result;

}

void MsgError(RetToken th) {
	switch (th) {
	case FILE_OPEN:
		fprintf(stderr, "%s\n", "ERROR: When openning file");
		exit(0);
		break;
	case FILE_I:
		fprintf(stderr, "%s\n", "ERROR: When read from file");
		exit(0);
		break;
	case FILE_O:
		fprintf(stderr, "%s\n", "ERROR: When write to file");
		exit(0);
		break;
	case ALLOC:
		fprintf(stderr, "%s\n", "ERROR: When allocated memory (malloc, realloc, new, etc)");
		exit(0);
		break;
	case FREE:
		fprintf(stderr, "%s\n", "ERROR: When free memory (free, delete)+ a");
		exit(0);
		break;
	case SUCCESS:
		break;
	case SKIP:
		break;
	}

}

int main(int argc, char const *argv[])
{
	PatriciaTree *tree = new PatriciaTree();
	Item th;
	th.path = new char[257];
	th.key = new char[257]; 
	PatriciaNode *tmp;
	PatriciaTree *o_O;
	Token state;
	RetToken returned;

	//th.path = NULL;
	while ((state = ReadLine(stdin, &th)) != Exit) {
		switch (state) {
		case Skip:
			break;
		case Insert:
			returned = tree->Insert(th.key, th.val);
			if (returned == SUCCESS) {
				//std::cout << "OK" << std::endl;
				fprintf(stdout, "%s\n", "OK");
			} else if (returned == SKIP) {
				//std::cout << "Exist" << std::endl;
				fprintf(stdout, "%s\n", "Exist");
			} else {
				MsgError(returned);
			}
			break;
		case Remove:
			//if (tree->Search(th.key) != NULL) {
			returned = tree->Delete(th.key);

			if (returned == SUCCESS) {
				//std::cout << "OK" << std::endl;
				fprintf(stdout, "%s\n", "OK");
			} else if (returned == SKIP) {
				//std::cout << "NoSuchWord" << std::endl;
				fprintf(stdout, "%s\n", "NoSuchWord");
			} else {
				MsgError(returned);
			}
			break;
		case Search:
			tmp = tree->Search(th.key);
			if (tmp) {
				//std::cout << "OK: " << tmp->value << std::endl;
				fprintf(stdout, "%s: %llu\n", "OK", tmp->value);
			} else {
				//std::cout << "NoSuchWord" << std::endl;
				fprintf(stdout, "%s\n", "NoSuchWord");
			}
			//std::cout << tree->size << std::endl;
			//tree->Print();

			break;
		case Save:

			returned = tree->Save(th.path);
			//delete [] th.path;
			//th.path = NULL;
			if (returned == SUCCESS) {
				std::cout << "OK" << std::endl;
				//fprintf(stdout, "%s\n", "OK");
				//th.path = NULL;
			} else {
				MsgError(returned);
			}
			break;
		case Load:
		{
			o_O = new PatriciaTree();
			tree->Clear();
			delete tree;
			returned = o_O->Load(th.path);

			if (returned == SUCCESS || returned == SKIP) {

				tree = o_O;
				std::cout << "OK" << std::endl;
				//fprintf(stdout, "%s\n", "OK");
			} else {
				o_O->Clear();
				delete o_O;
				MsgError(returned);
			}
			break;
		}
		case Error:
		{
			break;
		}
		case Exit:
			return 0;
		}
	}
	delete [] th.key;
	delete [] th.path;
	//tree->Clear();
	delete tree;

	return 0;
}


