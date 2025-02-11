// simpleC_complier_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
int main()
{
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
//#include <unistd.h>
#include <fcntl.h>

char *src_pos, *old_src_pos; //Դ���е�ǰ���ڴ����λ��
char *data, *old_data;    //���ݶ�

int *text, *old_text; //�����
int *symbol_table; //���ű�
int *current_id;        //��ǰ���ڴʷ������ı�ʶ��
int current_type;   //��ǰ���ʽ������
int token;     //��ǰ�ķ���
int token_val; //���Ŷ�Ӧ��ֵ
int *stack;    //ջ
int line;      //��ǰ����
int *main_func;  //ָ����ű�������������Ŀ

//�Ĵ���
int *pc;	// ��������� - �������ڼ���/�����ѧ��������,�����Ҫִ�е���һ��ָ��ĵ�ַ
int *bp;	// ջ��ָ��
int *sp;	// ջ��ָ��
int ax;		// �涨�������һ��ָ��ִ�к�Ľ��

//
int local_offset; //�ֲ�������ջ�е�ƫ��
				  //��������
enum { CHAR, INT, PTR };

//ָ��
enum {
	LEA, IMM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
	OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, MOD,
	OPEN, READ, CLOS, PRTF, MALC, FREE, MSET, MCMP, EXIT
};
//֧�ֵı�����(���ʷ�������next�����ɶ�Ӧ�ı��)
enum {
	Num = 128, Fun, Sys, Glo, Loc, Id, Char, Else, Enum, If, Int, Return, Sizeof,
	While, Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl,
	Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};
//���ű�ĸ���Ŀ
enum { Token, Hash, Name, Class, Type, Value, TempClass, TempType, TempValue, Size };

void next()
{
	char *begin_pos;
	int hash;
	while (token = *src_pos++)
	{
		if (token == '#')    //���ڲ�֧�ֺ�,����ֱ������
		{
			while (*src_pos && *src_pos != '\n')
			{
				++src_pos;
			}
		}
		else if (token == '\n')  //����+1
		{
			++line;
		}
		//�����Ϸ��ı�����(��Ϊ�Ѿ�Ԥ�ȴ�����һЩ��ʶ��,��if,else��)
		else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_'))
		{
			//��¼��ʶ������ʼλ��
			begin_pos = src_pos - 1;
			hash = token;
			//�����ʶ����hashֵ
			while ((*src_pos >= 'a' && *src_pos <= 'z') || (*src_pos >= 'A' && *src_pos <= 'Z') || (*src_pos >= '0' && *src_pos <= '9') || *src_pos == '_')
			{
				hash = hash * 33 + *src_pos++;
			}
			//��current_idָ����ű�
			current_id = symbol_table;
			while (current_id[Token])
			{
				//����hashֵ�����ַ����жϸñ�ʶ���Ƿ��Ѿ�������
				if (current_id[Hash] == hash && !memcmp((char *)current_id[Name], begin_pos, src_pos - begin_pos))
				{
					//��ѭ���˴���ñ�ʶ���Ѿ�����,��ȡ��token
					//Ȼ��return,����ñ�ʶ���Ѿ�ʶ��
					token = current_id[Token];
					return;
				}
				current_id = current_id + Size;
			}
			//����Ļ�,�����µı�ʶ�������ű���
			current_id[Name] = (int)begin_pos;
			current_id[Hash] = hash;
			token = current_id[Token] = Id;
			return;
		}
		//��������(֧��ʮ����,ʮ������,�˽���)
		else if (token >= '0' && token <= '9')
		{
			token_val = token - '0';
			//ʮ����
			if (token_val > 0)
			{
				while (*src_pos >= '0' && *src_pos <= '9')
				{
					token_val = token_val * 10 + *src_pos - '0';
					++src_pos;
				}
			}
			//ʮ������
			else if (*src_pos == 'x' || *src_pos == 'X')
			{
				token = *++src_pos;
				while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F'))
				{
					token_val = token_val * 16;
					if (token >= 'a')
					{
						token_val = token_val + token - 'a' + 10;
					}
					else if (token >= 'A')
					{
						token_val = token_val + token - 'A' + 10;
					}
					else
					{
						token_val = token_val + token - '0';
					}
				}
			}
			//�˽���
			else
			{
				while (*src_pos >= '0' && *src_pos <= '7')
				{
					token_val = token_val * 8 + *src_pos - '0';
					++src_pos;
				}
			}
			//����������֮��,����ʶ����ΪNum
			token = Num;
			return;
		}
		//�ַ���
		else if (token == '"' || token == '\'')
		{
			begin_pos = data;
			while (*src_pos && *src_pos != token)
			{
				token_val = *src_pos++;
				//����ת���
				if (token_val == '\\')
				{
					token_val = *src_pos++;
					//ֻ֧��\n,�����Ĳ��Ǻܴ��Ҫ
					if (token_val == 'n')
					{
						token_val = '\n';
					}
				}
				//������ַ���,���¼��data����
				if (token == '"')
				{
					*data = token_val;
					++data;
				}
			}
			++src_pos;
			//������ַ���,����ʼλ�ø���token_val(���ַ���ѭ����ʼ���Ѿ�����token_val��)
			if (token == '"')
			{
				token_val = (int)begin_pos;
			}
			//�����ַ���token����ΪNum
			else
			{
				token = Num;
			}
			return;
		}
		//���� //�� /
		else if (token == '/')
		{
			if (*src_pos == '/')
			{
				++src_pos;
				while (*src_pos && *src_pos != '\n')
				{
					++src_pos;
				}
			}
			else
			{
				token = Div;
				return;
			}
		}
		//����=��==
		else if (token == '=')
		{
			if (*src_pos != '=')
			{
				token = Assign;
			}
			else
			{
				++src_pos;
				token = Eq;
			}
			return;
		}
		//����+��++
		else if (token == '+')
		{
			if (*src_pos != '+')
			{
				token = Add;
			}
			else
			{
				++src_pos;
				token = Inc;
			}
			return;
		}
		//����-��--
		else if (token == '-')
		{
			if (*src_pos != '-')
			{
				token = Sub;
			}
			else
			{
				++src_pos;
				token = Dec;
			}
			return;
		}
		//����!=
		else if (token == '!')
		{
			if (*src_pos == '=')
			{
				++src_pos;
				token = Ne;
			}
			return;
		}
		//����<=��<<�Լ�< 
		else if (token == '<')
		{
			if (*src_pos == '=')
			{
				++src_pos;
				token = Le;
			}
			else if (*src_pos == '<')
			{
				++src_pos;
				token = Shl;
			}
			else
			{
				token = Lt;
			}
			return;
		}
		//����>��>=��>>
		else if (token == '>')
		{
			if (*src_pos == '=')
			{
				++src_pos;
				token = Ge;
			}
			else if (*src_pos == '>')
			{
				++src_pos;
				token = Shr;
			}
			else
			{
				token = Gt;
			}
			return;
		}
		//����|��||
		else if (token == '|')
		{
			if (*src_pos != '|')
			{
				token = Or;
			}
			else
			{
				++src_pos;
				token = Lor;
			}
			return;
		}
		//����&��&&
		else if (token == '&')
		{
			if (*src_pos != '&')
			{
				token = And;
			}
			else
			{
				token = Lan;
			}
			return;
		}
		//����^
		else if (token == '^')
		{
			token = Xor;
			return;
		}
		//����%
		else if (token == '%')
		{
			token = Mod;
			return;
		}
		//����*
		else if (token == '*')
		{
			token = Mul;
			return;
		}
		//����[
		else if (token == '[')
		{
			token = Brak;
			return;
		}
		//����?
		else if (token == '?')
		{
			token = Cond;
			return;
		}
		else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':')
		{
			return;
		}
	}
}

// �������ʽ
void expression(int level)
{
	int temp, *addr;
	if (!token)
	{
		printf("%d: unexpected eof in expression\n", line);
		exit(-1);
	}
	else if (token == Num)
	{
		*++text = IMM;
		*++text = token_val;
		next();
		current_type = INT;
	}
	else if (token == '"')
	{
		*++text = IMM;
		*++text = token_val;
		next();
		while (token == '"')
		{
			next();
		}
		//��ĩβ׷�ӽ�����
		data = (char *)((int)data + sizeof(int) & -sizeof(int));
		current_type = PTR;
	}
	else if (token == Sizeof)
	{
		next();
		if (token == '(')
		{
			next();
		}
		else
		{
			printf("%d: expected '('\n", line);
			exit(-1);
		}
		current_type = INT;
		if (token == Int)
		{
			next();
		}
		else if (token == Char)
		{
			next();
			current_type = CHAR;
		}
		while (token == Mul)
		{
			next();
			current_type = current_type + PTR;
		}
		if (token == ')')
		{
			next();
		}
		else
		{
			printf("%d: expected ')'\n", line);
			exit(-1);
		}
		*++text = IMM;
		if (current_type == PTR || current_type == INT)
		{
			*++text = sizeof(int);
		}
		else
		{
			*++text = sizeof(char);
		}
		current_type = INT;
	}
	else if (token == Id)
	{
		addr = current_id;
		next();
		if (token == '(')
		{
			next();
			temp = 0;
			while (token != ')')
			{
				expression(Assign);
				*++text = PUSH;
				++temp;
				if (token == ',')
				{
					next();
				}
			}
			next();
			if (addr[Class] == Sys)
			{
				*++text = addr[Value];
			}
			else if (addr[Class] == Fun)
			{
				*++text = CALL;
				*++text = addr[Value];
			}
			else
			{
				printf("%d: bad function call\n", line);
				exit(-1);
			}
			if (temp)
			{
				*++text = ADJ;
				*++text = temp;
			}
			current_type = addr[Type];
		}
		else if (addr[Class] == Num)
		{
			*++text = IMM;
			*++text = addr[Value];
			current_type = INT;
		}
		else
		{
			if (addr[Class] == Loc)
			{
				*++text = LEA;
				*++text = local_offset - addr[Value];
			}
			else if (addr[Class] == Glo)
			{
				*++text = IMM;
				*++text = addr[Value];
			}
			else
			{
				printf("%d: undefined variable\n", line);
				exit(-1);
			}
			current_type = addr[Type];
			*++text = (current_type == CHAR) ? LC : LI;
		}
	}
	else if (token == '(')
	{
		next();
		if (token == Int || token == Char)
		{
			temp = (token == Int) ? Int : Char;
			next();
			while (token == Mul)
			{
				next();
				temp = temp + PTR;
			}
			if (token == ')')
			{
				next();
			}
			else
			{
				printf("%d: bad cast\n", line);
				exit(-1);
			}
			expression(Inc);
			current_type = temp;
		}
		else
		{
			expression(Assign);
			if (token == ')')
			{
				next();
			}
			else
			{
				printf("%d: expected ')'\n", line);
				exit(-1);
			}
		}
	}
	else if (token == Mul)
	{
		next();
		expression(Inc);
		if (current_type > INT)
		{
			current_type = current_type - PTR;
		}
		else
		{
			printf("%d: bad dereference\n", line);
			exit(-1);
		}
		*++text = (current_type == CHAR) ? LC : LI;
	}
	else if (token == And)
	{
		next();
		expression(Inc);
		if (*text == LC || *text == LI)
		{
			--text;
		}
		else
		{
			printf("%d: bad address-of\n", line);
			exit(-1);
		}
		current_type = current_type + PTR;
	}
	else if (token == '!')
	{
		next();
		expression(Inc);
		*++text = PUSH;
		*++text = IMM;
		*++text = 0;
		*++text = EQ;
		current_type = INT;
	}
	else if (token == '~')
	{
		next();
		expression(Inc);
		*++text = PUSH;
		*++text = IMM;
		*++text = -1;
		*++text = XOR;
		current_type = INT;
	}
	else if (token == Add)
	{
		next();
		expression(Inc);
		current_type = INT;
	}
	else if (token == Sub)
	{
		next();
		*++text = IMM;
		if (token == Num)
		{
			*++text = -token_val;
			next();
		}
		else
		{
			*++text = -1;
			*++text = PUSH;
			expression(Inc);
			*++text = MUL;
		}
		current_type = INT;
	}
	else if (token == Inc || token == Dec)
	{
		temp = token;
		next();
		expression(Inc);
		if (*text == LC)
		{
			*text = PUSH;
			*++text = LC;
		}
		else if (*text == LI)
		{
			*text = PUSH;
			*++text = LI;
		}
		else
		{
			printf("%d: bad lvalue in pre-increment\n", line);
			exit(-1);
		}
		*++text = PUSH;
		*++text = IMM;

		*++text = (current_type > PTR) ? sizeof(int) : sizeof(char);
		*++text = (temp == Inc) ? ADD : SUB;
		*++text = (current_type == CHAR) ? SC : SI;
	}
	else
	{
		printf("%d: bad expression\n", line);
		exit(-1);
	}

	while (token >= level)
	{
		temp = current_type;
		if (token == Assign)
		{
			next();
			if (*text == LC || *text == LI)
			{
				*text = PUSH;
			}
			else
			{
				printf("%d: bad lvalue in assignment\n", line);
				exit(-1);
			}
			expression(Assign);
			current_type = temp;
			*++text = (current_type == CHAR) ? SC : SI;
		}
		else if (token == Cond)
		{
			next();
			*++text = JZ;
			addr = ++text;
			expression(Assign);
			if (token == ':')
			{
				next();
			}
			else
			{
				printf("%d: conditional missing colon\n", line);
				exit(-1);
			}
			*addr = (int)(text + 3);
			*++text = JMP;
			addr = ++text;
			expression(Cond);
			*addr = (int)(text + 1);
		}
		else if (token == Lor)
		{
			next();
			*++text = JNZ;
			addr = ++text;
			expression(Lan);
			*addr = (int)(text + 1);
			current_type = INT;
		}
		else if (token == Lan)
		{
			next();
			*++text = JZ;
			addr = ++text;
			expression(Or);
			*addr = (int)(text + 1);
			current_type = INT;
		}
		else if (token == Or)
		{
			next();
			*++text = PUSH;
			expression(Xor);
			*++text = OR;
			current_type = INT;
		}
		else if (token == Xor)
		{
			next();
			*++text = PUSH;
			expression(And);
			*++text = XOR;
			current_type = INT;
		}
		else if (token == And)
		{
			next();
			*++text = PUSH;
			expression(Eq);
			*++text = AND;
			current_type = INT;
		}
		else if (token == Eq)
		{
			next();
			*++text = PUSH;
			expression(Lt);
			*++text = EQ;
			current_type = INT;
		}
		else if (token == Ne)
		{
			next();
			*++text = PUSH;
			expression(Lt);
			*++text = NE;
			current_type = INT;
		}
		else if (token == Lt)
		{
			next();
			*++text = PUSH;
			expression(Shl);
			*++text = LT;
			current_type = INT;
		}
		else if (token == Gt)
		{
			next();
			*++text = PUSH;
			expression(Shl);
			*++text = GT;
			current_type = INT;
		}
		else if (token == Le)
		{
			next();
			*++text = PUSH;
			expression(Shl);
			*++text = LE;
			current_type = INT;
		}
		else if (token == Ge)
		{
			next();
			*++text = PUSH;
			expression(Shl);
			*++text = GE;
			current_type = INT;
		}
		else if (token == Shl)
		{
			next();
			*++text = PUSH;
			expression(Add);
			*++text = SHL;
			current_type = INT;
		}
		else if (token == Shr)
		{
			next();
			*++text = PUSH;
			expression(Add);
			*++text = SHR;
			current_type = INT;
		}
		else if (token == Add)
		{
			next();
			*++text = PUSH;
			expression(Mul);
			current_type = temp;
			if (current_type > PTR)
			{
				*++text = PUSH;
				*++text = IMM;
				*++text = sizeof(int);
				*++text = MUL;
			}
			*++text = ADD;
		}
		else if (token == Sub)
		{
			next();
			*++text = PUSH;
			expression(Mul);
			if (temp > PTR && temp == current_type)
			{
				*++text = SUB;
				*++text = PUSH;
				*++text = IMM;
				*++text = sizeof(int);
				*++text = DIV;
				current_type = INT;
			}
			else if ((current_type = temp) > PTR)
			{
				*++text = PUSH;
				*++text = IMM;
				*++text = sizeof(int);
				*++text = MUL;
				*++text = SUB;
			}
			else
			{
				*++text = SUB;
			}
		}
		else if (token == Mul)
		{
			next();
			*++text = PUSH;
			expression(Inc);
			*++text = MUL;
			current_type = INT;
		}
		else if (token == Div)
		{
			next();
			*++text = PUSH;
			expression(Inc);
			*++text = DIV;
			current_type = INT;
		}
		else if (token == Mod)
		{
			next();
			*++text = PUSH;
			expression(Inc);
			*++text = MOD;
			current_type = INT;
		}
		else if (token == Inc || token == Dec)
		{
			if (*text == LC)
			{
				*text = PUSH;
				*++text = LC;
			}
			else if (*text == LI)
			{
				*text = PUSH;
				*++text = LI;
			}
			else
			{
				printf("%d: bad lvalue in post-increment\n", line);
				exit(-1);
			}
			*++text = PUSH;
			*++text = IMM;
			*++text = (current_type > PTR) ? sizeof(int) : sizeof(char);
			*++text = (token == Inc) ? ADD : SUB;
			*++text = (current_type == CHAR) ? SC : SI;
			*++text = PUSH;
			*++text = IMM;
			*++text = (current_type > PTR) ? sizeof(int) : sizeof(char);
			*++text = (token == Inc) ? SUB : ADD;
			next();
		}
		else if (token == Brak)
		{
			next();
			*++text = PUSH;
			expression(Assign);
			if (token == ']')
			{
				next();
			}
			else
			{
				printf("%d: close bracket expected\n", line);
				exit(-1);
			}
			if (temp > PTR)
			{
				*++text = PUSH;
				*++text = IMM;
				*++text = sizeof(int);
				*++text = MUL;
			}
			else if (temp < PTR)
			{
				printf("%d: pointer type expected\n", line);
				exit(-1);
			}
			*++text = ADD;
			current_type = temp - PTR;
			*++text = (current_type == CHAR) ? LC : LI;
		}
		else
		{
			printf("%d: compiler error\n", line);
			exit(-1);
		}
	}
}
//�������
void statement()
{
	//*a:��������Ϊfalseʱ��ת�������
	//*b:Ϊ�˷�ֹ˳��ִ��if-else����,����ִ����true����ʱӦ����false����
	int *a, *b;
	//if���
	if (token == If)
	{
		next();
		if (token == '(')
		{
			next();
		}
		else
		{
			printf("%d: expected '('\n", line);
			exit(-1);
		}
		//�������ʽ
		expression(Assign);
		if (token == ')')
		{
			next();
		}
		else
		{
			printf("%d: expected ')'\n", line);
			exit(-1);
		}
		//��JZ����text��
		*++text = JZ;
		b = ++text;

		statement();

		if (token == Else)
		{
			next();

			//��JMP Bָ�����text����
			*b = (int)(text + 3);
			*++text = JMP;
			b = ++text;


			statement();
		}
		*b = (int)(text + 1);
	}
	//while���
	else if (token == While)
	{
		next();
		a = text + 1;
		if (token == '(')
		{
			next();
		}
		else
		{
			printf("%d: expected '('\n", line);
			exit(-1);
		}

		expression(Assign);

		if (token == ')')
		{
			next();
		}
		else
		{
			printf("%d: expected ')'\n", line);
			exit(-1);
		}
		*++text = JZ;
		b = ++text;

		statement();

		*++text = JMP;
		*++text = (int)a;
		*b = (int)(text + 1);
	}
	//Return���
	else if (token == Return)
	{
		next();
		if (token != ';')
		{
			expression(Assign);
		}
		//LEVָ���������ٺ�������ջ
		*++text = LEV;
		if (token == ';')
		{
			next();
		}
		else
		{
			printf("%d: expected ';'\n", line);
			exit(-1);
		}
	}
	//����
	else if (token == '{')
	{
		next();
		while (token != '}')
		{
			statement();
		}
		next();
	}
	else if (token == ';')
	{
		next();
	}
	else
	{
		expression(Assign);
		if (token == ';')
		{
			next();
		}
		else
		{
			printf("%d: expected ';'\n", line);
			exit(-1);
		}
	}
}



//�﷨��������
int grammar()
{
	//type:��¼��ǰ��ʶ������
	//enum_value:ö�ٱ�����ֵ
	//para_num:�����Ӿֲ������ĸ���
	int base_type, type, enum_value, para_num;

	line = 1;
	next();
	while (token)
	{
		base_type = INT;
		//int��
		if (token == Int)
		{
			next();
		}
		//char��
		else if (token == Char)
		{
			next();
			type = CHAR;
		}
		//enum��
		else if (token == Enum)
		{
			next();
			//ȥ����Ŀո�
			if (token != '{')
			{
				next();
			}
			//����enum
			if (token == '{')
			{
				next();
				enum_value = 0;
				//ֱ��enum��������
				while (token != '}')
				{
					//enum��ֵ�����ַ�ʽ,һ��Ĭ�ϴ�0��ʼ,����һ�ֿ����Լ����и�ֵ
					//���1
					if (token != Id)
					{
						printf("%d: bad enum identifier\n", line);
						return -1;
					}
					next();
					//���2
					if (token == Assign)
					{
						next();
						if (token != Num)
						{
							printf("%d: bad enum initializer\n", line);
							return -1;
						}
						enum_value = token_val;
						next();
					}
					//����ǰ�ı�ʶ������ű���
					current_id[Class] = Num;
					current_id[Type] = INT;
					current_id[Value] = enum_value++;
					//��δ����,��������
					if (token == ',')
					{
						next();
					}
				}
				next();
			}
		}
		//���������������������
		while (token != ';' && token != '}')
		{
			type = base_type;
			//ָ�����
			while (token == Mul)
			{
				next();
				type = type + PTR;
			}
			if (token != Id)
			{
				printf("%d: bad variable declaration\n", line);
				return -1;
			}
			//�жϱ���/�����Ƿ��Ѿ�����
			if (current_id[Class])
			{
				printf("%d: multiple defination\n", line);
				return -1;
			}
			next();
			current_id[Type] = type;
			//��������
			if (token == '(')
			{
				current_id[Class] = Fun;
				//��¼�ú����ĵ�ַ
				current_id[Value] = (int)(text + 1);
				next();
				para_num = 0;
				//��������
				while (token != ')')
				{
					type = INT;
					if (token == Int)
					{
						next();
					}
					else if (token == Char)
					{
						next();
						type = CHAR;
					}
					while (token == Mul)
					{
						next();
						type = type + PTR;
					}
					if (token != Id)
					{
						printf("%d: bad parameter declaration\n", line);
						return -1;
					}
					if (current_id[Class] == Loc)
					{
						printf("%d: multiple defination\n", line);
						return -1;
					}
					//����һϵ�в������ǽ�ʵ�ε���Ϣ���浽Tempxxx��,���βε���Ϣ���浽xxx��
					current_id[TempClass] = current_id[Class];
					current_id[Class] = Loc;
					current_id[TempType] = current_id[Type];
					current_id[Type] = type;
					current_id[TempValue] = current_id[Value];
					current_id[Value] = para_num++;
					next();
					//�����δ����,����
					if (token == ',')
					{
						next();
					}
				}
				next();
				//ֻ֧�������Ͷ�����һ��
				if (token != '{')
				{
					printf("%d: bad function defination\n", line);
					return -1;
				}
				local_offset = ++para_num;
				next();
				//�����������˺�����,�Ȱѱ���������
				//��ѭc89����,���������ڿ�Ŀ�ͷ����
				while (token == Int || token == Char)
				{
					if (token == Int)
					{
						type = Int;
					}
					else
					{
						type = Char;
					}
					next();
					while (token != ';')
					{
						type = base_type;
						while (token == Mul)
						{
							next();
							type = type + PTR;
						}
						if (token != Id)
						{
							printf("%d: bad local declaration\n", line);
							return -1;
						}
						if (current_id[Class] == Loc)
						{
							printf("%d: multiple local variable defination\n", line);
							return -1;
						}
						//����һϵ�в������ǽ�ȫ�ֱ�������Ϣ���浽Tempxxx��,���ֲ���������Ϣ���浽xxx��
						current_id[TempClass] = current_id[Class];
						current_id[Class] = Loc;
						current_id[TempType] = current_id[Type];
						current_id[Type] = type;
						current_id[TempValue] = current_id[Value];
						current_id[Value] = ++para_num;
						next();
						if (token == ',')
						{
							next();
						}
					}
					next();
				}
				//Ϊ�ֲ���������ջ����ռ�
				*++text = ENT;
				*++text = para_num - local_offset;
				while (token != '}')
				{
					statement();			// �������
				}
				//�����������,��ջ
				*++text = LEV;
				//�ָ�ȫ�ֱ�������Ϣ
				current_id = symbol_table;
				while (current_id[Token])
				{
					if (current_id[Class] == Loc)
					{
						current_id[Class] = current_id[TempClass];
						current_id[Type] = current_id[TempType];
						current_id[Value] = current_id[TempValue];
					}
					current_id = current_id + Size;
				}
			}
			//ȫ�ֱ���
			else
			{
				current_id[Class] = Glo;
				current_id[Value] = (int)data;
				data = data + sizeof(int);
			}
			if (token == ',')
			{
				next();
			}
		}
		next();
	}
}

/*
int main()
{
	int a;
	a = 1 + 2;
	printf("%d\n", a);
	return 0;
}
*/

int run()
{
	int i, *temp;
	while (1)
	{
		i = *pc++;
		if (i == LEA)
		{
			ax = (int)(bp + *pc++);
		}
		else if (i == IMM)
		{
			ax = *pc++;
		}
		else if (i == JMP)
		{
			pc = (int *)*pc;
		}
		else if (i == CALL)
		{
			*--sp = (int)(pc + 1);
			pc = (int *)*pc;
		}
		else if (i == JZ)
		{
			pc = ax ? pc + 1 : (int *)*pc;
		}
		else if (i == JNZ)
		{
			pc = ax ? (int *)*pc : pc + 1;
		}
		else if (i == ENT)
		{
			*--sp = (int)bp;
			bp = sp;
			sp = sp - *pc++;
		}
		else if (i == ADJ)
		{
			sp = sp + *pc++;
		}
		else if (i == LEV)
		{
			sp = bp;
			bp = (int *)*sp++;
			pc = (int *)*sp++;
		}
		else if (i == LI)
		{
			ax = *(int *)ax;
		}
		else if (i == LC)
		{
			ax = *(char *)ax;
		}
		else if (i == SI)
		{
			*(int *)*sp++ = ax;
		}
		else if (i == SC)
		{
			ax = *(char *)*sp++ = ax;
		}
		else if (i == PUSH)
		{
			*--sp = ax;
		}
		else if (i == OR)
		{
			ax = *sp++ | ax;
		}
		else if (i == XOR)
		{
			ax = *sp++ ^ ax;
		}
		else if (i == AND)
		{
			ax = *sp++ & ax;
		}
		else if (i == EQ)					// =
		{
			ax = *sp++ == ax;
		}
		else if (i == NE)
		{
			ax = *sp++ != ax;
		}
		else if (i == LT)
		{
			ax = *sp++ < ax;
		}
		else if (i == GT)
		{
			ax = *sp++ > ax;
		}
		else if (i == LE)
		{
			ax = *sp++ <= ax;
		}
		else if (i == GE)
		{
			ax = *sp++ >= ax;
		}
		else if (i == SHL)
		{
			ax = *sp++ << ax;
		}
		else if (i == SHR)
		{
			ax = *sp++ >> ax;
		}
		else if (i == ADD)				// ��
		{
			ax = *sp++ + ax;
		}
		else if (i == SUB)				// ��
		{
			ax = *sp++ - ax;
		}
		else if (i == MUL)				// ��
		{
			ax = *sp++ * ax;
		}
		else if (i == DIV)				// ��
		{
			ax = *sp++ / ax;
		}
		else if (i == MOD)				// %
		{
			ax = *sp++ % ax;
		}
		else if (i == OPEN)				// open
		{
			ax = open((char *)sp[1], *sp);
		}
		else if (i == READ)				// read
		{
			ax = read(sp[2], (char *)sp[1], *sp);
		}
		else if (i == CLOS)
		{
			ax = close(*sp);
		}
		else if (i == PRTF)				// printf
		{
			temp = sp + pc[1];
			ax = printf((char *)temp[-1], temp[-2], temp[-3], temp[-4], temp[-5], temp[-6]);	// ͨ���Ĵ��� ax ���ؽ��: a = 3
		}
		else if (i == MALC)				// malloc
		{
			ax = (int)malloc(*sp);
		}
		else if (i == FREE)				// free
		{
			free((void *)*sp);
		}
		else if (i == MSET)
		{
			ax = (int)memset((char *)sp[2], sp[1], *sp);
		}
		else if (i == MCMP)
		{
			ax = memcmp((char *)sp[2], (char *)sp[1], *sp);
		}
		else if (i == EXIT)					// exit �����˳�
		{
			printf("exit(%d)\n", *sp);
			return *sp;
		}
		else
		{
			printf("unknown instruction = %d\n", i);
			return -1;
		}
	}

}

int main(int argc, char **argv)
{
	int fd, pool_size, i;
	int *temp;
	int res;
	++argv;
	//��С
	pool_size = 256 * 1024;

	//������������ռ�
	if (!(symbol_table = (int*)malloc(pool_size)))
	{
		printf("could not malloc for symbol table\n");
		return -1;
	}
	if (!(text = old_text = (int*)malloc(pool_size)))
	{
		printf("could not malloc for text segment\n");
		return -1;
	}
	if (!(data = old_data = (char*)malloc(pool_size)))
	{
		printf("could not malloc for data segment\n");
		return -1;
	}
	if (!(stack = (int*)malloc(pool_size)))
	{
		printf("could not malloc for stack\n");
		return -1;
	}

	//init area
	memset(symbol_table, 0, pool_size);
	memset(text, 0, pool_size);
	memset(data, 0, pool_size);
	memset(stack, 0, pool_size);
	//�Ƚ���Щ���Ŵ�����ű���
	src_pos = "char else enum if int return sizeof while "
		"open read close printf malloc free memset memcmp exit void main";

	//Ԥ�Ƚ��ؼ��ִ�����ű���
	i = Char;
	while (i <= While)
	{
		next();
		current_id[Token] = i++;
	}
	//Ԥ�Ƚ�ϵͳ����������ű���
	i = OPEN;
	while (i <= EXIT)
	{
		next();
		current_id[Class] = Sys;
		current_id[Type] = INT;
		current_id[Value] = i++;
	}
	//����main�������
	next();
	//��void�����Char(�Ͼ�ֻ֧��int char����ָ��)
	current_id[Token] = Char;
	next();
	//ָ��main������Ӧ�ķ��ű���Ŀ
	main_func = current_id;

	if (!(src_pos = old_src_pos = (char*)malloc(pool_size)))
	{
		printf("could not malloc for source code\n");
		return -1;
	}
	memset(src_pos, 0, pool_size);
	//��Դ�ļ�����ȡ��src_pos��
	if ((fd = open(*argv, O_RDONLY)) < 0)
	{
		printf("could't open %s\n", *argv);
		return -1;
	}
	if ((i = read(fd, src_pos, pool_size - 1)) <= 0)
	{
		printf("read soucre code error with code %d\n", i);
		return -1;
	}


	//�ͷ���Դ
	close(fd);

	//�﷨����
	grammar();

	//
	if (!(pc = (int *)main_func[Value]))
	{
		printf("main() not defined\n");
		return -1;
	}

	sp = (int *)((int)stack + pool_size);
	*--sp = EXIT;
	*--sp = PUSH;
	temp = sp;
	*--sp = argc;
	*--sp = (int)argv;
	*--sp = (int)temp;

	res = run();
	free(old_src_pos);
	free(stack);
	free(old_data);
	free(old_text);
	free(symbol_table);

	getchar();
	return res;
}

