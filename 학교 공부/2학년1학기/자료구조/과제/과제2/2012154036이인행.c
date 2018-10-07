#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// db �����Ǵ� ��� C:\Users\Administrator\Documents\Visual Studio 2010\Projects\test\test

void Start(); // ó�� ���α׷� ���� �Լ�
int get_s_id_len(); // �л� ID�� ���̸� ��� ���� �Լ�
void get_name(FILE **, char *, int); // student.db�� �л� �̸� �Է��� ���� �Լ�
void get_s_id(FILE **, FILE **, int, int); // �л� ID�� �Է� �޴� �Լ�
int another_st(); // �л��� ������ �� �������� ����� �Լ�
void prt_eval(); // �� ���� �޴� ����� ���� �Լ�
void get_eval(FILE **); // �� ������ �ޱ� ���� �Լ�
int confirm_eval(FILE **); //�� ������ �Ϻ��ϰ� ���� �ߴ��� �ٽ��ѹ� Ȯ���ϴ� �Լ�
void create_eval_db(FILE **, FILE **, FILE **); // evaluaion_name.db�� ����� ���� �Լ�

int main()
{
	int sel; // �� �޴� ������ ���� int ����
	int s_id_len; // student ID�� ���̸� �޴� ����
	int s_cnt = 0; // �л� ���� ���ϱ� ���� ����
	int i = 0, j = 0; // ��� ���� ����
	FILE *st = NULL; // student.db�� �����ϱ� ���� ����
	FILE *st2 = NULL; // student.db���� s_id �ߺ��� ���� ��� �����ִ� ����
	FILE *evalu = NULL; // evaluation.db�� �����ϱ� ���� ����
	FILE *id_score = NULL; // �� ���� ���� �л��� ID�� ������ �޴� db�� �����ϱ� ���� ����

	Start();
	while (1)
	{
		scanf("%d", &sel); // DB�� �������� ������ ����
		switch (sel) // switch ���� �̿��� DB ���� ����
		{
		case 1:
			s_id_len = get_s_id_len(); // Student ID�� ���̸� ��ȯ�ϴ� �Լ� ȣ�� �� s_id_len ������ ����

			while (1) // �л����� ������ ��� �Է� �ޱ� ���� while��
			{
				get_name(&st, "student.db", s_cnt); // �л��� �̸��� �޴� �Լ� ȣ��
				s_cnt++; // �л� ���� ������Ŵ
				get_s_id(&st, &st2, s_cnt,s_id_len); // �л� ID �Է¹ޱ� �� �ߺ� �˻� �ϴ� �Լ� ȣ��
				i = another_st(); // �л��� ������ �� �������� ����� �Լ� ȣ��
				if (i == 0) // �л��� ������ �� �Է¹��� �ʴ´ٸ�
					break; // ���Ϲ��� ���� ����
			}
			// student.db �ۼ� �Ϸ� ---> ����Լ� 4��

			while (1) // �� ������ �Է� �ޱ� ���� while��
			{
				prt_eval(); // �� ���� �޴� ����� ���� �Լ� ȣ��
				get_eval(&evalu); // �� ������ DB�� ����ϱ� ���� �Լ� ȣ��
				i = confirm_eval(&evalu); 
				if (i != 0) // 0�̶�� �� ���� ����Ʈ���� �ٽ�
					break; // 0�� �ƴ϶�� �� ���� db ��ħ 
			}
			// evaluation.db �ۼ� �Ϸ� ---> ����Լ� 3��

			create_eval_db(&evalu, &st, &id_score); // evaluation_name.db�� �����ϱ� ���� �Լ� ȣ��

			j = 1; // db�� �����Ǹ� switch case�� �����ϰ� ���������� ���� ���� ����
			break; // case1 ��

		case 0: // db ������ ���Ѵٰ��ϸ� ���α׷� ����
			printf("\nThank you for using! \n\n");
			exit(0);

		default: // 0,1�� �ƴ� �߸� ���ý� ��� �޼���
			printf("[-] Wrong Choice! Please Re Select  \n");
			break;
		}
		if (j == 1) // switch case���� ������ ���� ����
			break;
	}

	// ��� DB�� ���������� ����!
	printf("\n\n [[ Success Create Student Management DB ]] \n\n");
	return 0;
}

void Start()
{
	printf("Welcome to Student Management Program \n\n"); // ���α׷� �λ縻
	printf("Do you want to create DB ? Yes: 1  No: 0 \n\n"); // DB ���� ����
}

int get_s_id_len()
{
	int s_id_len; // student ID�� ���̸� �޴� ����
	printf("\nPlease enter number of digit for student ID (ID Length): \n\n"); // �л� ID ���� ���� �ޱ�
	while (1)
	{
		scanf("%d", &s_id_len);
		if (s_id_len <= 0 || s_id_len>15) // �����Է� Ȥ�� �ʹ� ���� ���� �Է½� ���� �޼���
			printf("\n[-] Please enter student ID 1~15\n\n"); // ���� �޼���
		else
			break;
	}
	return s_id_len; // �л� ID ���̸� ��ȯ
}

void get_name(FILE **st, char *name, int s_cnt)
{
	int i; // ��� ���� ����
	char *last_name; // last name�� �޴� ����
	char *first_name; // first name�� �޴� ����

	last_name = (char *)malloc(20 * sizeof(char)); // last_name ���� �Ҵ�
	first_name = (char *)malloc(20 * sizeof(char)); // first_name ���� �Ҵ�

	i = s_cnt;

	*st = fopen(name, "a"); // student.db�� �Է��ϱ� ���� ����
	if (i == 0) // ���� ���� �Է��̶��
		fprintf(*st, "   NAME                 STUDET-ID \n"); //���� �Է½� student.db ��� ����

	while (1) // last name�� ���� �ͼ��� �ڵ鸵�� ���� ���Ϲ�
	{
		printf("\nPlease enter last name: \n\n"); // last name �Է� �ޱ�
		scanf("%s", last_name); // last_name ������ �Է¹ޱ�
		if (strlen(last_name)>19) // last name�� ���̰� �ʹ� ��ٸ� ���� �޼���
				printf("\n[-] Wrong last name!! \n\n");
		else
		{
			fprintf(*st, "%d %s ", s_cnt, last_name); // last name�� �����̶�� db�� �Է�
			break;
		}
	}

	while (1) // first name�� ���� �ͼ��� �ڵ鸵�� ���� ���Ϲ�
	{
		printf("\nPlease enter first name: \n\n"); // first name �Է¹ޱ�
		scanf("%s", first_name); // first_name ������ �Է� �ޱ�
		if (strlen(first_name)>19) // first name�� ���̰� �ʹ� ��ٸ� ���� �޼���
			printf("\n[-] Wrong first name!! \n\n");
		else
		{
			fprintf(*st, "%s\t\t", first_name); // first name�� �����̶�� db�� �Է�
			break;
		}
	}
	fclose(*st); // ���� ��� ������ �ݾ��ָ鼭 ���� ����
}

void get_s_id(FILE **st, FILE **st2, int s_cnt, int s_id_len)
{
	int i, j; // ��� ���� ����
	int s_id_res; // evaluate.db�� fscanf�� �б� ���� ����
	char *s_id; // Student ID�� �޴� ����
	char *s_id_tmp; // fscanf�� �ߺ� �˻縦 ���� �ӽ÷� �����ϴ� ����
	char *last_name; // last name�� �޴� ����
	char *first_name; // first name�� �޴� ����

	last_name = (char *)malloc(20 * sizeof(char)); // last_name ���� �Ҵ�
	first_name = (char *)malloc(20 * sizeof(char)); // first_name ���� �Ҵ�
	s_id = (char *)malloc(20 * sizeof(char)); // �����Ҵ�
	s_id_tmp = (char *)malloc(20 * sizeof(char)); // ���� �Ҵ�

	*st = fopen("student.db", "a"); // �л� ID�� ����ϱ� ���� ���� ����
	printf("\nPlease enter ID number: \n\n"); // �л� ID �Է� �ޱ�

	if (s_cnt != 1)  // �Է� �޴� �л� ������ ���ʰ� �ƴ϶��
	{
		*st2 = fopen("student.db", "r"); // �ؿ��� fscanf�� ����ϱ� ���� r���� ������

		while (1) // �л� ID�� �߸��Ȱ� ���͸� ���� while��
		{
			j = 0; // fseek ��� ���� ����
			scanf("%s", s_id); // s_id ������ �л� ID �Է� �ޱ�
			strcpy(s_id_tmp, s_id); // �ߺ� �˻縦 ���� s_id_tmp�� s_id ���� ����
			while (1) // �л� ID�� �ߺ��� �˻��ϱ� ���� while��
			{
				if (j == 0) // fscanf�� student.db�� ó�� �д� �ٴ� ����
				{
					// ���⼭ fseek�� ����ϴ� ������ student.db�� �� ���� NAME, STUDENT-ID��
					// ���ֱ� ������ fseek�� ������� �ʴ´ٸ� fscanf�� �����͸� �о� �� ���� ����.
					fseek(*st2, 34, 0); // �� �Ʒ� eval_name.db���� �׽�Ʈ �Ϸ�� ����
					j++;
				}

				// student.db ���� ������ �����鿡 ���� ������ ���پ� �޾ƿ�
				s_id_res = fscanf(*st2, "%d%s%s%s", &s_cnt, last_name, first_name, s_id);

				// student.db���� �о�� �л� ID ���� s_id ������ ����Ǿ� �ִ� �����̰�
				// ����ڰ� ����� ���ϴ� s_id_tmp �� �ߺ� �Ǵ��� �˻��Ѵ�
				if (strcmp(s_id_tmp, s_id) == 0)
				{
					// strcmp�� �̿��� �� ��
					// �ߺ��̶�� ���� �޼��� �� scanf�� �̿��� s_id�� �ٽ� ����
					printf("\nID number %s already exist. Please enter again : \n\n", s_id_tmp);
					scanf("%s", s_id_tmp);
					j = 0; // ���� �ߺ��̶�� j = 0���� ���������ν� ������ ó������ �ٽ� �����鼭 ����
				}
				else // �ߺ��� �ƴϸ鼭
				{
					if (s_id_res == EOF) // ������ ������ �� �о��ٸ� 
						break; // ������ �� �о��� ������ ���Ϲ��� ���� ����
				}
			}
			// �л� �ߺ��˻� while�� ��

			if (atoi(s_id_tmp) <= 0) // �л� ID�� ���� �����̸� ���� �޼���
				printf("\n[-] Wrong Student ID!! \n\n");

			else if (strlen(s_id_tmp) != s_id_len) // �Լ� ���ڷ� ���� �л� ID ���̿� ���� ��ġ���� ������
			{								  // �����޼���
				printf("[-] You enter %d digits ID number. \n", strlen(s_id_tmp));
				printf("[-] You are required %d digits ID number. \n\n", s_id_len);
			}
			else
			{
				fprintf(*st, "%s\n", s_id_tmp); // s_id_tmp�� ���� �����̶�� db�� �Է�
				fclose(*st); // �Ѹ��� ������ �� �ԷµǸ� ���� ����
				fclose(*st2); // r���� ���� �ִ� student.db�� �ݾ���
				break;
			}
		}
	}
	else // �Է� �޴� �л� ������ ó���̶�� �ߺ� �˻�� �� �ʿ䰡 ����
	{
		while (1) // �л� ID�� �ͼ��� �ڵ鸵 �ϱ����� while ��
		{
			scanf("%s", s_id); // s_id ������ �л� ID �Է� �ޱ�
			if (atoi(s_id) <= 0) // �л� ID�� ���� �����̸� ���� �޼���
				printf("\n[-] Wrong Student ID!! \n\n");

			else if (strlen(s_id) != s_id_len) // �Լ� ���ڷ� ���� �л� ID ���̿� ���� ��ġ���� ������
			{								  // �����޼���
				printf("[-] You enter %d digits ID number. \n", strlen(s_id));
				printf("[-] You are required %d digits ID number. \n\n", s_id_len);
			}
			else
			{
				fprintf(*st, "%s\n", s_id); // s_id_tmp�� ���� �����̶�� db�� �Է�
				fclose(*st); // �Ѹ��� ������ �� �ԷµǸ� ���� ����
				break; // while���� ���� ����
			}
		}
	}

}

int another_st()
{
	int sel; // �޴� ������ ���� ����

	printf("\nAnother Student ? Yes: 1  No: 0 \n\n"); // �ٸ� �л��� ������ �Է����� ����
	scanf("%d", &sel);
	while (1) // �ͼ����� ���� while��
	{
		if (sel == 0) // ���̻� �л��� ������ �Է����� �ʴ´ٸ� break
			break;
		else if (sel != 1) // 0�� �ƴϰ� 1�� �ƴϸ�
		{
			printf("[-] Wrong Select!! Please Select 1 or 2 \n");
			scanf("%d", &sel);
		}
		else // �л��� ������ �� �Է¹޴� �ٰ� �ص� break
			break;
	}
	return sel;
}

void prt_eval()
{
	printf("\n==============================================\n\n");
	printf("Evaluation Criteria \n\n");
	printf("    1. Assignment \n\n");
	printf("    2. Project \n\n");
	printf("    3. Laboratory \n\n");
	printf("    4. Attendance \n\n");
	printf("    5. Participation \n\n");
	printf("    6. Quiz \n\n");
	printf("    7. Midterm Exam \n\n");
	printf("    8. Final Exam \n\n");
	printf("    9. Exit \n\n\n");
}

void get_eval(FILE **evalu)
{
	int res_per; // �򰡱��� �ۼ�Ʈ�� ����� �ޱ� ���� ����
	int eval_sel; // �� ������ ��ȣ�� �����ϱ� ���� ����
	int per = 0; // �򰡱��� �ۼ�Ʈ�� �ޱ� ���� ����
	int sel; // �޴� ������ ���� ����
	int i; // ��� ���� ����
	char *eval_name; // �򰡱����� �Է� �ޱ� ���� ����

	eval_name = (char *)malloc(20 * sizeof(char)); // �򰡱��� �Է� ���� �Ҵ�

	while (1) // �� ���� �Է��� ���� while��
	{
		i = 0;
		*evalu = fopen("evaluation.db", "w"); // evaluation.db�� �����ϱ� ���� ���� ����
		printf("Please select number to evaluate and percentage \n\n");
		printf("Example : 1 20 \n\n");
		res_per = 0; // ���� �ۼ�Ʈ�� 0���� �ʱ�ȭ

		while (1)
		{
			scanf("%d", &eval_sel); // eval_sel ������ �� ������ ����
			if (eval_sel == 9)// ���� ������ exit�̸�
			{				// �Է� �޴� �� ������ ���߰� ���� ������ ����
				fclose(*evalu);
				break;
			}
			else if (eval_sel <= 0 || eval_sel >= 10) // 1-9 �޴��� �ƴϸ� ���� �޼���
			{
				printf("\n[-] Wrong Choice! Select [ 1-9 ] \n\n");
				break;
			}
			else // ������ ����� ��ٸ�
			{
				switch (eval_sel) // ������� ���ÿ� ���� �� ������ ����
				{
				case 1:
					eval_name = "Assignment";
					break;
				case 2:
					eval_name = "Project";
					break;
				case 3:
					eval_name = "Laboratory";
					break;
				case 4:
					eval_name = "Attendance";
					break;
				case 5:
					eval_name = "Participation";
					break;
				case 6:
					eval_name = "Quiz";
					break;
				case 7:
					eval_name = "Midterm-Exam";
					break;
				case 8:
					eval_name = "Final-Exam";
					break;
				}
				// ����ڰ� ������ ���ڿ� �� ������ db�� ����
				fprintf(*evalu, "%d %s ", eval_sel, eval_name);

				scanf("%d", &per); // �� ���ؿ� ���� �ۼ�Ʈ�� per ������ �Է� ����
			}

			res_per += per; // �ۼ�Ʈ�� ���ۼ�Ʈ ���� ���� �Ǿ����� ���
			if (res_per > 100) // ���� �ۼ�Ʈ�� 100�ۼ�Ʈ�� �Ѵ´ٸ�
			{
				printf("\n[-] Exceed 100% ! \n\n");
				printf("[-] If you want to enter from the first, press 1 \n");
				printf("[-] If you want to modify previous value, press 2 \n\n");
				scanf("%d", &sel);
				if (sel == 1) // 1�� �����ϸ� �ʱ� �ۼ�Ʈ �޴� while������
				{
					i = 1;
					printf("\nYou select menu 1\n");
					printf("Percentage Initialized\n\n");
					break; // �׵��� ��� �Ǿ��� evaluation.db�� ������ �ʱ�ȭ ��
				}
				else if (sel == 2) // 2�� �����ϸ� ������ �� ���ؿ� ���� �ۼ�Ʈ�� �ٽ� ����
				{
					while (1) // �ۼ�Ʈ�� 100���� ����� ���� while��
					{
						res_per = res_per - per; // ���� �ۼ�Ʈ�� �����
						printf("Current Percentage is %d \n", res_per); // ���� ���ۼ�Ʈ���� ������
						printf("\nPlease enter percentage again %d \n\n", 100 - res_per);
						scanf("%d", &per);
						res_per += per;
						if (res_per == 100) // �����ۼ�Ʈ�� 100�ۼ�Ʈ�̸� ù��° ���Ϲ��� ���� ������
						{				// �׿� ���ÿ� db�� �ۼ�Ʈ�� ������
							fprintf(*evalu, "%d\n", per);
							fclose(*evalu); // evaluation.db�� ������ ������
							break;
						}
						else
							printf("\n[-] Not 100% ! Enter right percentage \n\n");
					}
				}
				if (res_per == 100) // ���⼭ �ٽ� �˻��ؼ� ��ü �� ���ؿ� ���� ���Ϲ��� ��������
					break;
			}
			else if (res_per == 100) // ������ ���� 100�ۼ�Ʈ�� �ʰ����� �ʰ� 
									 // ��Ȯ�ϰ� 100�ۼ�Ʈ�� ���缭 �Է��ߴٸ�
			{
				fprintf(*evalu, "%d\n", per); // ������ �ۼ�Ʈ�� db�� �����ϰ�
				fclose(*evalu); // evaluation.db�� ������ ������
				break;
			}
			else // ���� �ۼ�Ʈ�� 100�ۼ�Ʈ�� �ƴ϶��
			{
				fprintf(*evalu, "%d\n", per); // �� ���ؿ� ���� �ۼ�Ʈ�� db�� ����
				printf("\nPlease select another number to evaluate and percentage \n\n");
			}
		}
		if(i!=1)
			break; // evaluation.db�� ���� while���� ������ ���� ����
	}
}

int confirm_eval(FILE **evalu)
{
	int eval_sel; // �� ������ ��ȣ�� �����ϱ� ���� ����
	int eval_res; // evaluate.db�� fscanf�� �б� ���� ����
	int per = 0; // �򰡱��� �ۼ�Ʈ�� �ޱ� ���� ����
	int sel; // �޴� ������ ���� ����
	char *eval_name; // �򰡱����� �Է� �ޱ� ���� ����

	eval_name = (char *)malloc(20 * sizeof(char)); // �򰡱��� �Է� ���� �Ҵ�

	printf("\n\n\n");
	printf("You select \n\n");
	*evalu = fopen("evaluation.db", "r"); // evaluation.db�� ������ �ޱ� ���� ����
	while (1) // db�� ������ ���پ� �б� ���� while��
	{
		eval_res = fscanf(*evalu, "%d%s%d", &eval_sel, eval_name, &per); // ���پ� ������ ����
		if (eval_res == EOF) // ������ �������� break
			break;
		if (strlen(eval_name) <= 7) // Quiz ���� ª�� ������ eval_name�� ��2��
			printf("   %d.  %s\t\t%d\n", eval_sel, eval_name, per);
		else // ������ �� 1���� ����
			printf("   %d.  %s\t%d\n", eval_sel, eval_name, per);
	}
	fclose(*evalu);

	printf("\nIs it correct? Yes: 1 No: 0 \n\n");
	printf("If you press \"No\", it will start from the first.\n\n");
	scanf("%d", &sel);
	
	return sel;
}

void create_eval_db(FILE **evalu, FILE **st, FILE **id_score)
{
	int eval_res; // evaluate.db�� fscanf�� �б� ���� ����
	int eval_sel; // �� ������ ��ȣ�� �����ϱ� ���� ����
	int per = 0; // �򰡱��� �ۼ�Ʈ�� �ޱ� ���� ����
	int i; // ��� ���� ����ϴ� ����
	int s_id_res; // evaluate.db�� fscanf�� �б� ���� ����
	int s_cnt = 0; // �л� ���� ���ϱ� ���� ����
	char *eval_name; // �򰡱����� �Է� �ޱ� ���� ����
	char *id_score_db; // id_score�� db�� ����� ���� db�� �̸��� �����ϴ� ����
	char *last_name; // last name�� �޴� ����
	char *first_name; // first name�� �޴� ����
	char *s_id; // Student ID�� �޴� ����
	double score = 0; // �л��� ������ �ޱ� ���� ����

	eval_name = (char *)malloc(20 * sizeof(char)); // �򰡱��� �Է� ���� �Ҵ�
	id_score_db = (char *)malloc(20 * sizeof(char)); // id_score�� db�� �̸��� �����ϱ� ���� ���� �Ҵ�
	last_name = (char *)malloc(20 * sizeof(char)); // last_name ���� �Ҵ�
	first_name = (char *)malloc(20 * sizeof(char)); // first_name ���� �Ҵ�
	s_id = (char *)malloc(20 * sizeof(char)); // �����Ҵ�

	*evalu = fopen("evaluation.db", "r"); // �� ������ �̸��� ������ ��� ���� ����
	*st = fopen("student.db", "r"); // student_id�� ������ ��� ���� ����
	while (1)
	{
		eval_res = fscanf(*evalu, "%d%s%d", &eval_sel, eval_name, &per); // evaluation.db�� ���پ� ����
		if (eval_res == EOF) // ������ �� �о��ٸ� break
			break;

		id_score_db = strcat(eval_name, ".db"); // eval_name.db�� ����� ���� ����

		*id_score = fopen(id_score_db, "a"); // eval_name.db ����

		fprintf(*id_score, "STUDENT-ID    score1\n");

		i = 0; // fseek ��� ���� i�� 0���� �ʱ�ȭ
		while (1)
		{
			// s_id�� ������ ��� ���� student.db�� ������ ���پ� ����
			if (i == 0) // fscanf�� student.db�� ó�� �д� �ٴ� ����
			{
				// ���⼭ fseek�� ����ϴ� ������ student.db�� �� ���� NAME, STUDENT-ID��
				// ���ֱ� ������ fseek�� ������� �ʴ´ٸ� fscanf�� �����͸� �о� �� ���� ����.
				fseek(*st, 34, 0);
				i++;
			}

			s_id_res = fscanf(*st, "%d %s %s %s", &s_cnt, last_name, first_name, s_id);
			if (s_id_res == EOF) // s_id�� ������ �� �о����� db�� �����ϰ� break
			{
				fclose(*id_score);
				break;
			}
			fprintf(*id_score, "   %s        %.1lf\n", s_id, score);
		}
	}
	// db ������ ���� ������� ������ �ٽ� �ݾ���
	fclose(*evalu);
	fclose(*st);
}