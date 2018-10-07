#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// db 생성되는 경로 C:\Users\Administrator\Documents\Visual Studio 2010\Projects\test\test

void Start(); // 처음 프로그램 실행 함수
int get_s_id_len(); // 학생 ID의 길이를 얻기 위한 함수
void get_name(FILE **, char *, int); // student.db에 학생 이름 입력을 위한 함수
void get_s_id(FILE **, FILE **, int, int); // 학생 ID를 입력 받는 함수
int another_st(); // 학생의 정보를 더 받을건지 물어보는 함수
void prt_eval(); // 평가 기준 메뉴 출력을 위한 함수
void get_eval(FILE **); // 평가 기준을 받기 위한 함수
int confirm_eval(FILE **); //평가 기준을 완벽하게 선택 했는지 다시한번 확인하는 함수
void create_eval_db(FILE **, FILE **, FILE **); // evaluaion_name.db를 만들기 위한 함수

int main()
{
	int sel; // 각 메뉴 선택을 위한 int 변수
	int s_id_len; // student ID의 길이를 받는 변수
	int s_cnt = 0; // 학생 수를 구하기 위한 변수
	int i = 0, j = 0; // 제어를 위한 변수
	FILE *st = NULL; // student.db를 생성하기 위한 변수
	FILE *st2 = NULL; // student.db에서 s_id 중복을 위해 잠시 열어주는 변수
	FILE *evalu = NULL; // evaluation.db를 생성하기 위한 변수
	FILE *id_score = NULL; // 평가 기준 별로 학생의 ID와 점수를 받는 db를 생성하기 위한 변수

	Start();
	while (1)
	{
		scanf("%d", &sel); // DB를 생성할지 안할지 선택
		switch (sel) // switch 문을 이용해 DB 생성 선택
		{
		case 1:
			s_id_len = get_s_id_len(); // Student ID의 길이를 반환하는 함수 호출 후 s_id_len 변수에 저장

			while (1) // 학생들의 정보를 계속 입력 받기 위한 while문
			{
				get_name(&st, "student.db", s_cnt); // 학생의 이름을 받는 함수 호출
				s_cnt++; // 학생 수를 증가시킴
				get_s_id(&st, &st2, s_cnt,s_id_len); // 학생 ID 입력받기 및 중복 검사 하는 함수 호출
				i = another_st(); // 학생의 정보를 더 받을건지 물어보는 함수 호출
				if (i == 0) // 학생의 정보를 더 입력받지 않는다면
					break; // 와일문을 빠져 나감
			}
			// student.db 작성 완료 ---> 사용함수 4개

			while (1) // 평가 기준을 입력 받기 위한 while문
			{
				prt_eval(); // 평가 기준 메뉴 출력을 위한 함수 호출
				get_eval(&evalu); // 평가 기준을 DB에 기록하기 위한 함수 호출
				i = confirm_eval(&evalu); 
				if (i != 0) // 0이라면 평가 기준 프린트부터 다시
					break; // 0이 아니라면 평가 기준 db 마침 
			}
			// evaluation.db 작성 완료 ---> 사용함수 3개

			create_eval_db(&evalu, &st, &id_score); // evaluation_name.db를 생성하기 위한 함수 호출

			j = 1; // db가 생성되면 switch case를 완전하게 빠져나가기 위해 변수 조작
			break; // case1 끝

		case 0: // db 생성을 안한다고하면 프로그램 종료
			printf("\nThank you for using! \n\n");
			exit(0);

		default: // 0,1이 아닌 잘못 선택시 경고 메세지
			printf("[-] Wrong Choice! Please Re Select  \n");
			break;
		}
		if (j == 1) // switch case문을 완전히 빠져 나감
			break;
	}

	// 모든 DB가 정상적으로 생성!
	printf("\n\n [[ Success Create Student Management DB ]] \n\n");
	return 0;
}

void Start()
{
	printf("Welcome to Student Management Program \n\n"); // 프로그램 인사말
	printf("Do you want to create DB ? Yes: 1  No: 0 \n\n"); // DB 생성 질문
}

int get_s_id_len()
{
	int s_id_len; // student ID의 길이를 받는 변수
	printf("\nPlease enter number of digit for student ID (ID Length): \n\n"); // 학생 ID 길이 정보 받기
	while (1)
	{
		scanf("%d", &s_id_len);
		if (s_id_len <= 0 || s_id_len>15) // 음수입력 혹은 너무 높은 숫자 입력시 에러 메세지
			printf("\n[-] Please enter student ID 1~15\n\n"); // 에러 메세지
		else
			break;
	}
	return s_id_len; // 학생 ID 길이를 반환
}

void get_name(FILE **st, char *name, int s_cnt)
{
	int i; // 제어를 위한 변수
	char *last_name; // last name을 받는 변수
	char *first_name; // first name을 받는 변수

	last_name = (char *)malloc(20 * sizeof(char)); // last_name 동적 할당
	first_name = (char *)malloc(20 * sizeof(char)); // first_name 동적 할당

	i = s_cnt;

	*st = fopen(name, "a"); // student.db에 입력하기 위해 오픈
	if (i == 0) // 만약 최초 입력이라면
		fprintf(*st, "   NAME                 STUDET-ID \n"); //최초 입력시 student.db 양식 생성

	while (1) // last name에 대한 익셉션 핸들링을 위한 와일문
	{
		printf("\nPlease enter last name: \n\n"); // last name 입력 받기
		scanf("%s", last_name); // last_name 변수에 입력받기
		if (strlen(last_name)>19) // last name의 길이가 너무 길다면 에러 메세지
				printf("\n[-] Wrong last name!! \n\n");
		else
		{
			fprintf(*st, "%d %s ", s_cnt, last_name); // last name이 정상이라면 db에 입력
			break;
		}
	}

	while (1) // first name에 대한 익셉션 핸들링을 위한 와일문
	{
		printf("\nPlease enter first name: \n\n"); // first name 입력받기
		scanf("%s", first_name); // first_name 변수에 입력 받기
		if (strlen(first_name)>19) // first name의 길이가 너무 길다면 에러 메세지
			printf("\n[-] Wrong first name!! \n\n");
		else
		{
			fprintf(*st, "%s\t\t", first_name); // first name이 정상이라면 db에 입력
			break;
		}
	}
	fclose(*st); // 열어 줬던 파일을 닫아주면서 내용 갱신
}

void get_s_id(FILE **st, FILE **st2, int s_cnt, int s_id_len)
{
	int i, j; // 제어를 위한 변수
	int s_id_res; // evaluate.db의 fscanf를 읽기 위한 변수
	char *s_id; // Student ID를 받는 변수
	char *s_id_tmp; // fscanf로 중복 검사를 위해 임시로 저장하는 변수
	char *last_name; // last name을 받는 변수
	char *first_name; // first name을 받는 변수

	last_name = (char *)malloc(20 * sizeof(char)); // last_name 동적 할당
	first_name = (char *)malloc(20 * sizeof(char)); // first_name 동적 할당
	s_id = (char *)malloc(20 * sizeof(char)); // 동적할당
	s_id_tmp = (char *)malloc(20 * sizeof(char)); // 동적 할당

	*st = fopen("student.db", "a"); // 학생 ID를 기록하기 위해 파일 오픈
	printf("\nPlease enter ID number: \n\n"); // 학생 ID 입력 받기

	if (s_cnt != 1)  // 입력 받는 학생 정보가 최초가 아니라면
	{
		*st2 = fopen("student.db", "r"); // 밑에서 fscanf를 사용하기 위해 r모드로 열어줌

		while (1) // 학생 ID의 잘못된값 필터를 위한 while문
		{
			j = 0; // fseek 제어를 위한 변수
			scanf("%s", s_id); // s_id 변수에 학생 ID 입력 받기
			strcpy(s_id_tmp, s_id); // 중복 검사를 위해 s_id_tmp에 s_id 값을 복사
			while (1) // 학생 ID의 중복을 검사하기 위한 while문
			{
				if (j == 0) // fscanf로 student.db를 처음 읽는 다는 조건
				{
					// 여기서 fseek을 사용하는 이유는 student.db의 맨 위가 NAME, STUDENT-ID로
					// 되있기 때문에 fseek을 사용하지 않는다면 fscanf로 데이터를 읽어 올 수가 없다.
					fseek(*st2, 34, 0); // 맨 아래 eval_name.db에서 테스트 완료된 값임
					j++;
				}

				// student.db 에서 각각의 변수들에 대한 정보를 한줄씩 받아옴
				s_id_res = fscanf(*st2, "%d%s%s%s", &s_cnt, last_name, first_name, s_id);

				// student.db에서 읽어온 학생 ID 값이 s_id 변수에 저장되어 있는 상태이고
				// 사용자가 등록을 원하는 s_id_tmp 와 중복 되는지 검사한다
				if (strcmp(s_id_tmp, s_id) == 0)
				{
					// strcmp를 이용해 비교 후
					// 중복이라면 에러 메세지 후 scanf를 이용해 s_id를 다시 받음
					printf("\nID number %s already exist. Please enter again : \n\n", s_id_tmp);
					scanf("%s", s_id_tmp);
					j = 0; // 만약 중복이라면 j = 0으로 제어함으로써 파일의 처음부터 다시 읽으면서 비교함
				}
				else // 중복이 아니면서
				{
					if (s_id_res == EOF) // 파일의 끝까지 다 읽었다면 
						break; // 끝까지 다 읽었기 때문에 와일문을 빠져 나감
				}
			}
			// 학생 중복검사 while문 끝

			if (atoi(s_id_tmp) <= 0) // 학생 ID의 값이 음수이면 에러 메세지
				printf("\n[-] Wrong Student ID!! \n\n");

			else if (strlen(s_id_tmp) != s_id_len) // 함수 인자로 받은 학생 ID 길이와 값이 일치하지 않으면
			{								  // 에러메세지
				printf("[-] You enter %d digits ID number. \n", strlen(s_id_tmp));
				printf("[-] You are required %d digits ID number. \n\n", s_id_len);
			}
			else
			{
				fprintf(*st, "%s\n", s_id_tmp); // s_id_tmp의 값이 정상이라면 db에 입력
				fclose(*st); // 한명의 정보가 다 입력되면 파일 갱신
				fclose(*st2); // r모드로 열려 있던 student.db를 닫아줌
				break;
			}
		}
	}
	else // 입력 받는 학생 정보가 처음이라면 중복 검사는 할 필요가 없음
	{
		while (1) // 학생 ID를 익셉션 핸들링 하기위한 while 문
		{
			scanf("%s", s_id); // s_id 변수에 학생 ID 입력 받기
			if (atoi(s_id) <= 0) // 학생 ID의 값이 음수이면 에러 메세지
				printf("\n[-] Wrong Student ID!! \n\n");

			else if (strlen(s_id) != s_id_len) // 함수 인자로 받은 학생 ID 길이와 값이 일치하지 않으면
			{								  // 에러메세지
				printf("[-] You enter %d digits ID number. \n", strlen(s_id));
				printf("[-] You are required %d digits ID number. \n\n", s_id_len);
			}
			else
			{
				fprintf(*st, "%s\n", s_id); // s_id_tmp의 값이 정상이라면 db에 입력
				fclose(*st); // 한명의 정보가 다 입력되면 파일 갱신
				break; // while문을 빠져 나감
			}
		}
	}

}

int another_st()
{
	int sel; // 메뉴 선택을 위한 변수

	printf("\nAnother Student ? Yes: 1  No: 0 \n\n"); // 다른 학생의 정보도 입력할지 질문
	scanf("%d", &sel);
	while (1) // 익셉션을 위한 while문
	{
		if (sel == 0) // 더이상 학생의 정보를 입력하지 않는다면 break
			break;
		else if (sel != 1) // 0도 아니고 1도 아니면
		{
			printf("[-] Wrong Select!! Please Select 1 or 2 \n");
			scanf("%d", &sel);
		}
		else // 학생의 정보를 더 입력받는 다고 해도 break
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
	int res_per; // 평가기준 퍼센트의 결과를 받기 위한 변수
	int eval_sel; // 평가 기준의 번호를 선택하기 위한 변수
	int per = 0; // 평가기준 퍼센트를 받기 위한 변수
	int sel; // 메뉴 선택을 위한 변수
	int i; // 제어를 위한 변수
	char *eval_name; // 평가기준을 입력 받기 위한 변수

	eval_name = (char *)malloc(20 * sizeof(char)); // 평가기준 입력 동적 할당

	while (1) // 평가 기준 입력을 위한 while문
	{
		i = 0;
		*evalu = fopen("evaluation.db", "w"); // evaluation.db를 생성하기 위한 파일 오픈
		printf("Please select number to evaluate and percentage \n\n");
		printf("Example : 1 20 \n\n");
		res_per = 0; // 누적 퍼센트를 0으로 초기화

		while (1)
		{
			scanf("%d", &eval_sel); // eval_sel 변수에 평가 기준을 넣음
			if (eval_sel == 9)// 만약 선택이 exit이면
			{				// 입력 받던 평가 기준을 멈추고 파일 저장후 나감
				fclose(*evalu);
				break;
			}
			else if (eval_sel <= 0 || eval_sel >= 10) // 1-9 메뉴가 아니면 에러 메세지
			{
				printf("\n[-] Wrong Choice! Select [ 1-9 ] \n\n");
				break;
			}
			else // 선택이 제대로 됬다면
			{
				switch (eval_sel) // 사용자의 선택에 따라서 평가 기준을 나눔
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
				// 사용자가 선택한 숫자와 평가 기준을 db에 저장
				fprintf(*evalu, "%d %s ", eval_sel, eval_name);

				scanf("%d", &per); // 평가 기준에 대한 퍼센트를 per 변수에 입력 받음
			}

			res_per += per; // 퍼센트가 몇퍼센트 까지 누적 되었는지 계산
			if (res_per > 100) // 누적 퍼센트가 100퍼센트가 넘는다면
			{
				printf("\n[-] Exceed 100% ! \n\n");
				printf("[-] If you want to enter from the first, press 1 \n");
				printf("[-] If you want to modify previous value, press 2 \n\n");
				scanf("%d", &sel);
				if (sel == 1) // 1을 선택하면 초기 퍼센트 받는 while문으로
				{
					i = 1;
					printf("\nYou select menu 1\n");
					printf("Percentage Initialized\n\n");
					break; // 그동안 기록 되었던 evaluation.db의 내용이 초기화 됨
				}
				else if (sel == 2) // 2를 선택하면 마지막 평가 기준에 대한 퍼센트를 다시 받음
				{
					while (1) // 퍼센트를 100으로 만들기 위한 while문
					{
						res_per = res_per - per; // 현재 퍼센트를 계산함
						printf("Current Percentage is %d \n", res_per); // 현재 몇퍼센트인지 보여줌
						printf("\nPlease enter percentage again %d \n\n", 100 - res_per);
						scanf("%d", &per);
						res_per += per;
						if (res_per == 100) // 누적퍼센트가 100퍼센트이면 첫번째 와일문을 빠져 나오고
						{				// 그와 동시에 db에 퍼센트를 저장함
							fprintf(*evalu, "%d\n", per);
							fclose(*evalu); // evaluation.db의 내용을 저장함
							break;
						}
						else
							printf("\n[-] Not 100% ! Enter right percentage \n\n");
					}
				}
				if (res_per == 100) // 여기서 다시 검사해서 전체 평가 기준에 대한 와일문을 빠져나감
					break;
			}
			else if (res_per == 100) // 마지막 까지 100퍼센트를 초과하지 않고 
									 // 정확하게 100퍼센트를 맞춰서 입력했다면
			{
				fprintf(*evalu, "%d\n", per); // 마지막 퍼센트를 db에 저장하고
				fclose(*evalu); // evaluation.db의 내용을 저장함
				break;
			}
			else // 누적 퍼센트가 100퍼센트가 아니라면
			{
				fprintf(*evalu, "%d\n", per); // 평가 기준에 대한 퍼센트를 db에 저장
				printf("\nPlease select another number to evaluate and percentage \n\n");
			}
		}
		if(i!=1)
			break; // evaluation.db에 대한 while문을 완전히 빠져 나감
	}
}

int confirm_eval(FILE **evalu)
{
	int eval_sel; // 평가 기준의 번호를 선택하기 위한 변수
	int eval_res; // evaluate.db의 fscanf를 읽기 위한 변수
	int per = 0; // 평가기준 퍼센트를 받기 위한 변수
	int sel; // 메뉴 선택을 위한 변수
	char *eval_name; // 평가기준을 입력 받기 위한 변수

	eval_name = (char *)malloc(20 * sizeof(char)); // 평가기준 입력 동적 할당

	printf("\n\n\n");
	printf("You select \n\n");
	*evalu = fopen("evaluation.db", "r"); // evaluation.db의 정보를 받기 위해 오픈
	while (1) // db의 내용을 한줄씩 읽기 위한 while문
	{
		eval_res = fscanf(*evalu, "%d%s%d", &eval_sel, eval_name, &per); // 한줄씩 내용을 읽음
		if (eval_res == EOF) // 끝까지 다읽으면 break
			break;
		if (strlen(eval_name) <= 7) // Quiz 같이 짧은 길이의 eval_name은 탭2개
			printf("   %d.  %s\t\t%d\n", eval_sel, eval_name, per);
		else // 나머진 탭 1개로 정렬
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
	int eval_res; // evaluate.db의 fscanf를 읽기 위한 변수
	int eval_sel; // 평가 기준의 번호를 선택하기 위한 변수
	int per = 0; // 평가기준 퍼센트를 받기 위한 변수
	int i; // 제어를 위해 사용하는 변수
	int s_id_res; // evaluate.db의 fscanf를 읽기 위한 변수
	int s_cnt = 0; // 학생 수를 구하기 위한 변수
	char *eval_name; // 평가기준을 입력 받기 위한 변수
	char *id_score_db; // id_score의 db를 만들기 위해 db의 이름을 저장하는 변수
	char *last_name; // last name을 받는 변수
	char *first_name; // first name을 받는 변수
	char *s_id; // Student ID를 받는 변수
	double score = 0; // 학생의 점수를 받기 위한 변수

	eval_name = (char *)malloc(20 * sizeof(char)); // 평가기준 입력 동적 할당
	id_score_db = (char *)malloc(20 * sizeof(char)); // id_score의 db의 이름을 저장하기 위해 동적 할당
	last_name = (char *)malloc(20 * sizeof(char)); // last_name 동적 할당
	first_name = (char *)malloc(20 * sizeof(char)); // first_name 동적 할당
	s_id = (char *)malloc(20 * sizeof(char)); // 동적할당

	*evalu = fopen("evaluation.db", "r"); // 평가 과목의 이름의 정보를 얻기 위해 오픈
	*st = fopen("student.db", "r"); // student_id의 정보를 얻기 위해 오픈
	while (1)
	{
		eval_res = fscanf(*evalu, "%d%s%d", &eval_sel, eval_name, &per); // evaluation.db를 한줄씩 읽음
		if (eval_res == EOF) // 파일을 다 읽었다면 break
			break;

		id_score_db = strcat(eval_name, ".db"); // eval_name.db를 만들기 위해 저장

		*id_score = fopen(id_score_db, "a"); // eval_name.db 생성

		fprintf(*id_score, "STUDENT-ID    score1\n");

		i = 0; // fseek 제어를 위해 i를 0으로 초기화
		while (1)
		{
			// s_id의 정보를 얻기 위해 student.db의 정보를 한줄씩 읽음
			if (i == 0) // fscanf로 student.db를 처음 읽는 다는 조건
			{
				// 여기서 fseek을 사용하는 이유는 student.db의 맨 위가 NAME, STUDENT-ID로
				// 되있기 때문에 fseek을 사용하지 않는다면 fscanf로 데이터를 읽어 올 수가 없다.
				fseek(*st, 34, 0);
				i++;
			}

			s_id_res = fscanf(*st, "%d %s %s %s", &s_cnt, last_name, first_name, s_id);
			if (s_id_res == EOF) // s_id의 정보를 다 읽었으면 db를 저장하고 break
			{
				fclose(*id_score);
				break;
			}
			fprintf(*id_score, "   %s        %.1lf\n", s_id, score);
		}
	}
	// db 생성을 위해 열어줬던 파일을 다시 닫아줌
	fclose(*evalu);
	fclose(*st);
}