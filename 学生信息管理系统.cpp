#include <stdio.h>
#include <process.h>
#include <string.h>
#include <windows.h>
#define Maxnum 100 //�洢�������Ϣ��Ŀ

//�ṹ���飬���ڴ洢���е���Ϣ
struct student {
	int Num;            //��¼���
	int Idnumber;       //��¼ѧ��
	char Name[15];      //��¼����
	char Sex[10];		//��¼�Ա�
	int Age;			//����
	char Hometown[15];  //��¼��͢��ַ
	int Score[6];       //��¼�ɼ�,����Ӣ�ﻯ��
} info[Maxnum];

int count; //ȫ�ֱ�������¼��һ���ж��ٸ���Ϣ��Ŀ  ʵ������count+1������

//��������
void InputChoice();
void AddInfo();
void DeleteInfo();
void ModifyInfo();
void SearchInfo();
void ShowAllInfo();
void Greeting(int);
void Save();

//������
int	main() {
	FILE* fp1;
	FILE* fp2;
	//���ļ������Ϣ���ݶ�ȡ���ṹ������
	//�ȶ�ȡѧ��������Ϣ
	if ((fp2 = fopen("StudentInfo.txt", "r")) == NULL) {
		printf("\t\t\t		�޷����ļ���\n");
		exit(0);
	}
	while (fscanf(fp2, "%d\t%s\t%s\t%s\t%d", &info[count].Idnumber, info[count].Name, info[count].Sex, info[count].Hometown, &info[count].Age) != EOF) {
		count++;
	}
	if (fclose(fp2)) {
		printf("\t\t\t		�޷��ر��ļ���\n");
		exit(0);
	}
	//�ٶ�ȡѧ���ɼ���Ϣ
	int t;	//�ڶ�ȡ����Ҫ�Թ�ĳЩ����
	count = 0;
	if ((fp1 = fopen("StudentScore.txt", "r")) == NULL) {
		printf("\t\t\t		�޷����ļ���\n");
		exit(0);
	}
	while (fscanf(fp1, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", &info[count].Num, &t, &info[count].Score[0], &info[count].Score[1], &info[count].Score[2], &info[count].Score[3], &info[count].Score[4], &info[count].Score[5]) != EOF) {
		count++;	//��ȡ����Ϣ��Ŀ
	}
	if (fclose(fp1)) {
		printf("\t\t\t		�޷��ر��ļ���\n");
		exit(0);
	}
	Greeting(1);
	InputChoice();  //�˵��ò��᷵����
}
//���˵�
void InputChoice() {
	int choice;
_A:
	system("cls");
	printf("\n\n");
	printf("\t\t\t		���˵�\n\n");
	printf("\t\t\t		��ѡ����Ĳ���:\n\n");
	printf("\t\t\t		1-���һ��ѧ����Ϣ\n");
	printf("\t\t\t		2-ɾ��һ��ѧ����Ϣ\n");
	printf("\t\t\t		3-�޸�һ��ѧ����Ϣ\n");
	printf("\t\t\t		4-����һ��ѧ����Ϣ\n");
	printf("\t\t\t		5-��ʾȫ��ѧ����Ϣ\n");
	printf("\t\t\t		0-�˳�����\n");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		AddInfo();
		break;
	case 2:
		DeleteInfo();
		break;
	case 3:
		ModifyInfo();
		break;
	case 4:
		SearchInfo();
		break;
	case 5:
		ShowAllInfo();
		break;
	case 0:Greeting(0);  //�˺�������Ϊ����Ψһ����
		break;
	}
	if (choice > 5) {
		printf("\t\t\t		��������ȷ�����֣�\n");
		system("pause");
		goto _A;
	}
}
//���ѧ����Ϣ
void AddInfo() {
	int choice, N;
	system("cls");
	printf("\n\n\t\t\t		����ִ����Ӳ�����������Ҫ������\n\n");
	while (1) {
		printf("\t\t\t		��������ӵ�ѧ����Ϣ�ĸ���\n");
		scanf("%d", &N);
		if (N > 0) {
			break;
		}
		else {
			printf("\t\t\t		������������\n");
			system("pause");
		}
	}
	for (int k = 0;k < N;k++) {
	_Again:
		printf("\t\t\t		������%d��ѧ������Ϣ\n", k);
		printf("\t\t\t		������ѧ����ѧ�š��������Ա����䡢��ͥסַ\n");
		scanf("%d %s %s %d %s", &info[count].Idnumber, info[count].Name, info[count].Sex, &info[count].Age, info[count].Hometown);
		fflush(stdin);
		for (int i = 0;i < count;i++) {		//���ڼ���Ƿ��Ѿ�����
			if (info[i].Idnumber == info[count].Idnumber) {
				printf("\t\t\t		�Ѵ��ڴ��˵���Ϣ��\n");
				while (1) {
					printf("\t\t\t		�����Ƿ�������ӣ�\n");
					printf("\t\t\t		1-�� 2-�񣬷������˵�\n");
					scanf("%d", &choice);
					if (choice == 1) {
						goto _Again;
					}
					else if (choice == 2) {
						printf("\t\t\t		���ڷ������˵�\n");
						system("pause");
						InputChoice();
					}
					else {
						printf("\t\t\t		������1��2��\n");
						system("pause");
					}
				}
			}
		}
		fflush(stdin);
		printf("\n\t\t\t		�������ѧ���ĸ��Ƴɼ����밴����Ӣ�ﻯ����˳������\n");
		scanf("%d %d %d %d %d %d", &info[count].Score[0], &info[count].Score[1], &info[count].Score[2], &info[count].Score[3], &info[count].Score[4], &info[count].Score[5]);
		info[count].Num = info[count - 1].Num + 1;
		count++;  //���������Ϣ��Ŀ��һ
	}
	Save();			//������ӵ���Ϣ���浽�ļ���
	printf("\t\t\t		��ӳɹ���\n");
	system("pause");
	printf("\t\t\t		���ڷ������˵���\n");
	system("pause");
	InputChoice();
}
//ɾ��ĳ��ѧ������Ϣ
void DeleteInfo() {
	char NAME[15];
	int way, ID, choice, Check = 0, Mark;  //Check�����ж��Ƿ���ڴ��˵���Ϣ��0��ʾ������;Mark���ڱ����ɾ������Ϣ���±�
	system("cls");
	printf("\n\n\t\t\t		����ִ��ɾ��������������Ҫ������\n\n");
_A:
	printf("\t\t\t		��ʹ�ã�\n");
	printf("\t\t\t		1-ѧ�Ż�2-���� ѡ�����\n");
	printf("\t\t\t		3-�ص����˵�\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		��������������ѧ��:\n");
		scanf("%d", &ID);
		for (int i = 0;i < count;i++) {
			if (info[i].Idnumber == ID) {
				Check = 1;  //��ʾ���ڴ��˵���Ϣ
				Mark = i;
			}
		}
		if (Check == 0) {
			printf("\t\t\t		�����ڴ��˵���Ϣ��\n");
			system("pause");
			while (1) {
				printf("\t\t\t		�Ƿ��������� 1-�������� 2-�������˵�\n");
				scanf("%d", &choice);
				if (choice == 1) {
					goto _A;
				}
				else if (choice == 2) {
					printf("\t\t\t		���ڷ������˵�\n");
					system("pause");
					InputChoice();
				}
				else {
					printf("\t\t\t		��������������1��2��\n");
					system("pause");
				}
			}
		}
		else if (Check == 1) {
			while (1) {		//ѯ���Ƿ�ȷ��ɾ��
				printf("\t\t\t		�Ƿ�ȷ��ɾ��ѧ��Ϊ%d��ѧ������Ϣ��\n", ID);
				printf("\t\t\t		1-�� 2-�񣬷����������� 3-�񣬷������˵�\n");
				scanf("%d", &choice);
				if (choice == 1) {
					for (int i = Mark;i < count - Mark - 1;i++) {	//�����е���Ϣ����ǰ�ƶ�һλ���������
						info[i].Idnumber = info[i + 1].Idnumber;
						strcpy(info[i].Name, info[i + 1].Name);
						strcpy(info[i].Sex, info[i + 1].Sex);
						info[i].Age = info[i + 1].Age;
						strcpy(info[i].Hometown, info[i + 1].Hometown);
						info[i].Score[0] = info[i + 1].Score[0];
						info[i].Score[1] = info[i + 1].Score[1];
						info[i].Score[2] = info[i + 1].Score[2];
						info[i].Score[3] = info[i + 1].Score[3];
						info[i].Score[4] = info[i + 1].Score[4];
						info[i].Score[5] = info[i + 1].Score[5];
					}
					count--;		//����Ϣ��Ŀ��һ
					Save();
					printf("\t\t\t		�ѳɹ�ɾ��ѧ��Ϊ%d��ѧ������Ϣ��\n", ID);
					system("pause");
					printf("\t\t\t		�����������˵�\n");
					system("pause");
					InputChoice();
				}
				else if (choice == 2) {
					goto _A;
				}
				else if (choice == 3) {
					printf("\t\t\t		���ڷ������˵�\n");
					system("pause");
					InputChoice();
				}
				else {
					printf("\t\t\t		������1��2��3��\n");
					system("pause");
				}
			}
		}
	}
	else if (way == 2) {
		printf("\t\t\t		������������������:\n");
		scanf("%s", NAME);
		for (int i = 0;i <= count;i++) {
			if (strcmp(NAME, info[i].Name) == 0) {
				Check = 1;  //��ʾ���ڴ��˵���Ϣ
				Mark = i;
			}
		}
		if (Check == 0) {
			printf("\t\t\t		�����ڴ��˵���Ϣ��\n");
			system("pause");
			while (1) {
				printf("\t\t\t		�Ƿ��������� 1-�������� 2-�������˵�\n");
				scanf("%d", &choice);
				if (choice == 1) {
					goto _A;
				}
				else if (choice == 2) {
					printf("\t\t\t		���ڷ������˵�\n");
					system("pause");
					InputChoice();
				}
				else {
					printf("\t\t\t		��������������1��2��\n");
					system("pause");
				}
			}
		}
		else {
			while (1) {
				printf("\t\t\t		�Ƿ�ȷ��ɾ������Ϊ%s��ѧ������Ϣ?\n", NAME);
				printf("\t\t\t		1-�� 2-�񣬷����������� 3-�񣬷������˵�\n");
				scanf("%d", &choice);
				if (choice == 1) {
					for (int i = Mark;i < count - Mark - 1;i++) {
						info[i].Idnumber = info[i + 1].Idnumber;
						strcpy(info[i].Name, info[i + 1].Name);
						strcpy(info[i].Sex, info[i + 1].Sex);
						info[i].Age = info[i + 1].Age;
						strcpy(info[i].Hometown, info[i + 1].Hometown);
						info[i].Score[0] = info[i + 1].Score[0];
						info[i].Score[1] = info[i + 1].Score[1];
						info[i].Score[2] = info[i + 1].Score[2];
						info[i].Score[3] = info[i + 1].Score[3];
						info[i].Score[4] = info[i + 1].Score[4];
						info[i].Score[5] = info[i + 1].Score[5];
					}
					count--;
					Save();
					printf("\t\t\t		�ѳɹ�ɾ������Ϊ%s��ѧ������Ϣ��\n", NAME);
					system("pause");
					printf("\t\t\t		�����������˵�\n");
					system("pause");
					InputChoice();
				}
				else if (choice == 2) {
					goto _A;
				}
				else if (choice == 3) {
					printf("\t\t\t		���ڷ������˵�\n");
					system("pause");
					InputChoice();
				}
				else {
					printf("\t\t\t		������1��2��3��\n");
					system("pause");
				}
			}
		}
	}
	else if (way == 3) {
		printf("\t\t\t		���ڷ������˵�\n");
		system("pause");
		InputChoice();
	}
	else {
		printf("\t\t\t		������1��2��3��\n");
		system("pause");
		goto _A;
	}
}
//�޸�ĳ��ѧ������Ϣ
void ModifyInfo() {
	int choice, ID, way, choice1;
	char NAME[15];
	system("cls");
	printf("\n\n\t\t\t		����ִ���޸Ĳ�����������Ҫ������\n\n");
_A:
	printf("\t\t\t		��ʹ�ã�\n");
	printf("\t\t\t		1-ѧ�Ż�2-���� ѡ�����\n");
	printf("\t\t\t		3-�ص����˵�\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		��������������ѧ��:\n");
		scanf("%d", &ID);
		for (int i = 0;i < count;i++) {
			if (ID == info[i].Idnumber) {
				printf("\t\t\t		��������Ҫ�޸ĵ���Ϣ\n");
				printf("\t\t\t		1-ѧ�� 2-���� 3-�Ա� 4-���� 5-��ͥסַ 6-���Ƴɼ�\n");  //ѧ�Ų��ܹ��ظ�
			_B:
				scanf("%d", &choice);
				switch (choice) {		//���ڷֱ��޸ĸ�����Ϣ
				case 1:
					while (1) {
						int tempID;
						printf("\t\t\t		�������µ�ѧ��\n");
						scanf("%d", &tempID);
						for (int j = 0;j < count;j++) {  //���ڼ��ѧ���Ƿ��ظ�
							if (info[j].Idnumber == tempID) {
								printf("\t\t\t		�Ѵ��ڴ�ѧ�ţ�\n");
								while (1) {
									printf("\t\t\t		�����Ƿ�������ӣ�\n");
									printf("\t\t\t		1-�� 2-�񣬷������˵�\n");
									scanf("%d", &choice);
									if (choice == 1) {
										printf("\t\t\t		���ٴ�����ѧ��\n");
										goto _B;
									}
									else if (choice == 2) {
										printf("\t\t\t		���ڷ������˵�\n");
										system("pause");
										InputChoice();
									}
									else {
										printf("\t\t\t		������1��2��\n");
										system("pause");
									}
								}
							}
						}
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							printf("\t\t\t		�ѽ�ѧ��Ϊ%d��ѧ����ѧ�Ÿ���Ϊ%d\n", info[i].Idnumber, tempID);
							info[i].Idnumber = tempID;
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 2:
					while (1) {
						char tempNAME[15];
						printf("\t\t\t		�������µ�����\n");
						scanf("%s", tempNAME);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Name, tempNAME);
							printf("\t\t\t		�ѽ�ѧ��Ϊ%d��ѧ������������Ϊ%s\n", info[i].Idnumber, info[i].Name);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 3:
					while (1) {
						char tempSEX[10];
						printf("\t\t\t		�������µ��Ա�\n");
						scanf("%s", tempSEX);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Sex, tempSEX);
							printf("\t\t\t		�ѽ�ѧ��Ϊ%d��ѧ�����Ա����Ϊ%s\n", info[i].Idnumber, info[i].Sex);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 4:
					while (1) {
						int tempAGE;
						printf("\t\t\t		�������µ�����\n");
						scanf("%d", &tempAGE);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							info[i].Age = tempAGE;
							printf("\t\t\t		�ѽ�ѧ��Ϊ%d��ѧ�����������Ϊ%d\n", info[i].Idnumber, info[i].Age);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 5:
					while (1) {
						char tempHOME[15];
						printf("\t\t\t		�������µļ�ͥסַ\n");
						scanf("%s", tempHOME);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Hometown, tempHOME);
							printf("\t\t\t		�ѽ�ѧ��Ϊ%d��ѧ���ļ�ͥסַ����Ϊ%s\n", info[i].Idnumber, info[i].Hometown);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 6:
					while (1) {
						int SCORE[6];
						printf("\t\t\t		�������µĸ��Ƴɼ�\n");
						printf("\t\t\t		��������Ӣ�ﻯ����˳������\n");
						for (int j = 0;j < 6;j++) {
							scanf("%d", &SCORE[j]);
						}
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							for (int j = 0;j < 6;j++) {
								info[i].Score[j] = SCORE[j];
							}
							printf("\t\t\t		�ѽ�ѧ��Ϊ%d��ѧ��������Ӣ�ﻯ���ɼ�����Ϊ%d %d %d %d %d %d\n", info[i].Idnumber, info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				}
				Save();
				printf("\t\t\t		���ڷ������˵�\n");
				system("pause");
				InputChoice();
			}
		}	//��������for����û���ҵ�Ŀ�꣬�Ż�ִ�����´���
		printf("\t\t\t		�����ڴ��˵���Ϣ��\n");
		system("pause");
		while (1) {
			printf("\t\t\t		�Ƿ��������룿1-�������� 2-�������˵�\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		���ڷ������˵�\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		��������������1��2��\n");
				system("pause");
			}
		}
	}
	else if (way == 2) {
		printf("\t\t\t		������������������:\n");
		scanf("%s", NAME);
		for (int i = 0;i < count;i++) {
			if ((strcmp(NAME, info[i].Name)) == 0) {
				printf("\t\t\t		��������Ҫ�޸ĵ���Ϣ\n");
				printf("\t\t\t		1-ѧ�� 2-���� 3-�Ա� 4-���� 5-��ͥסַ 6-���Ƴɼ�\n");
			_C:
				scanf("%d", &choice);
				switch (choice) {		//�ֱ��޸�
				case 1:
					while (1) {
						int tempID;
						printf("\t\t\t		�������µ�ѧ��\n");
						scanf("%d", &tempID);
						for (int j = 0;j < count;j++) {  //���ڼ��ѧ���Ƿ��ظ�
							if (info[j].Idnumber == tempID) {
								printf("\t\t\t		�Ѵ��ڴ�ѧ�ţ�\n");
								while (1) {
									printf("\t\t\t		�����Ƿ�������ӣ�\n");
									printf("\t\t\t		1-�� 2-�񣬷������˵�\n");
									scanf("%d", &choice);
									if (choice == 1) {
										printf("\t\t\t		���ٴ�����ѧ��\n");
										goto _C;
									}
									else if (choice == 2) {
										printf("\t\t\t		���ڷ������˵�\n");
										system("pause");
										InputChoice();
									}
									else {
										printf("\t\t\t		������1��2��\n");
										system("pause");
									}
								}
							}
						}
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							info[i].Idnumber = tempID;
							printf("\t\t\t		�ѽ�����Ϊ%s��ѧ����ѧ�Ÿ���Ϊ%d\n", info[i].Name, info[i].Idnumber);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 2:
					while (1) {
						char tempNAME[15];
						printf("\t\t\t		�������µ�����\n");
						scanf("%s", tempNAME);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							printf("\t\t\t		�ѽ�����Ϊ%s��ѧ������������Ϊ%s\n", info[i].Name, tempNAME);
							strcpy(info[i].Name, tempNAME);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 3:
					while (1) {
						char tempSEX[10];
						printf("\t\t\t		�������µ��Ա�\n");
						scanf("%s", tempSEX);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Sex, tempSEX);
							printf("\t\t\t		�ѽ�����Ϊ%s��ѧ�����Ա����Ϊ%s\n", info[i].Name, info[i].Sex);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 4:
					while (1) {
						int tempAGE;
						printf("\t\t\t		�������µ�����\n");
						scanf("%d", &tempAGE);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							info[i].Age = tempAGE;
							printf("\t\t\t		�ѽ�����Ϊ%s��ѧ�����������Ϊ%d\n", info[i].Name, info[i].Age);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 5:
					while (1) {
						char tempHOME[15];
						printf("\t\t\t		�������µļ�ͥסַ\n");
						scanf("%s", tempHOME);
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Hometown, tempHOME);
							printf("\t\t\t		�ѽ�����Ϊ%s��ѧ���ļ�ͥסַ����Ϊ%s\n", info[i].Name, info[i].Hometown);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				case 6:
					while (1) {
						int SCORE[6];
						printf("\t\t\t		�������µĸ��Ƴɼ�\n");
						printf("\t\t\t		��������Ӣ�ﻯ����˳������\n");
						for (int j = 0;j < 6;j++) {
							scanf("%d", &SCORE[j]);
						}
						printf("\t\t\t		�Ƿ�ȷ�����ģ�1-�� 2-��\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							for (int j = 0;j < 6;j++) {
								info[i].Score[j] = SCORE[j];
							}
							printf("\t\t\t		�ѽ�����Ϊ%s��ѧ��������Ӣ�ﻯ���ɼ�����Ϊ%d %d %d %d %d %d\n", info[i].Name, info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		������1��2��\n");
							system("pause");
						}
					}break;
				}
				Save();
				printf("\t\t\t		���ڷ������˵�\n");
				system("pause");
				InputChoice();
			}
		}	//��δ�ҵ�Ŀ��Ż�ִ�����´���
		printf("\t\t\t		�����ڴ��˵���Ϣ��\n");
		system("pause");
		while (1) {
			printf("\t\t\t		�Ƿ��������룿1-�������� 2-�������˵�\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		���ڷ������˵�\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		��������������1��2��\n");
				system("pause");
			}
		}
	}
	else if (way == 3) {
		printf("\t\t\t		���ڷ������˵�\n");
		system("pause");
		InputChoice();
	}
	else {
		printf("\t\t\t		������1��2��3��\n");
		system("pause");
		goto _A;
	}
}
//����ĳ��ѧ������Ϣ
void SearchInfo() {
	int way, ID, choice;
	char NAME[15];
	system("cls");
	printf("\n\n\t\t\t		����ִ�в��Ҳ�����������Ҫ������\n\n");
_A:
	printf("\t\t\t		��ʹ�ã�\n");
	printf("\t\t\t		1-ѧ�Ż�2-���� ѡ�����\n");
	printf("\t\t\t		3-�ص����˵�\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		��������������ѧ��:\n");
		scanf("%d", &ID);
		for (int i = 0;i < count;i++) {
			if (ID == info[i].Idnumber) {
				printf("\t\t\t		ѧ��%d��ѧ������ϢΪ��\n", info[i].Idnumber);
				printf("\t\t\t		����\t�Ա�\t����\tסַ\n");
				printf("\t\t\t		%s\t%s\t%d\t%s\n", info[i].Name, info[i].Sex, info[i].Age, info[i].Hometown);
				printf("\n\t\t\t		ѧ��%d��ѧ���ĳɼ�Ϊ��\n", info[i].Idnumber);
				printf("\t\t\t		����\t��ѧ\tӢ��\t����\t��ѧ\t����\n");
				printf("\t\t\t		%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
				system("pause");
				printf("\t\t\t		�����������˵�\n");
				system("pause");
				InputChoice();
			}
		}	//δ�ҵ�Ŀ��Ż�ִ�����´���
		printf("\t\t\t		�����ڴ��˵���Ϣ��\n");
		system("pause");
		while (1) {
			printf("\t\t\t		�Ƿ��������룿1-�������� 2-�������˵�\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		���ڷ������˵�\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		��������������1��2��\n");
				system("pause");
			}
		}
	}
	else if (way == 2) {
		printf("\t\t\t		������������������:\n");
		scanf("%s", NAME);
		for (int i = 0;i < count;i++) {
			if ((strcmp(NAME, info[i].Name)) == 0) {
				printf("\t\t\t		����Ϊ%s��ѧ������ϢΪ��\n", info[i].Name);
				printf("\t\t\t		ѧ��\t�Ա�\t����\tסַ\n");
				printf("\t\t\t		%d\t%s\t%d\t%s\n", info[i].Idnumber, info[i].Sex, info[i].Age, info[i].Hometown);
				printf("\n\t\t\t		����Ϊ%s��ѧ���ĳɼ�Ϊ��\n", info[i].Name);
				printf("\t\t\t		����\t��ѧ\tӢ��\t����\t��ѧ\t����\n");
				printf("\t\t\t		%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
				system("pause");
				printf("\t\t\t		�����������˵�\n");
				system("pause");
			}
		}InputChoice();
		//δ�ҵ�Ŀ��Ż�ִ�����´���
		printf("\t\t\t		�����ڴ��˵���Ϣ��\n");
		system("pause");
		while (1) {
			printf("\t\t\t		�Ƿ��������룿1-�������� 2-�������˵�\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		���ڷ������˵�\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		��������������1��2��\n");
				system("pause");
			}
		}
	}
	else if (way == 3) {
		printf("\t\t\t		���ڷ������˵�\n");
		system("pause");
		InputChoice();
	}
	else {
		printf("\t\t\t		������1��2��3��\n");
		system("pause");
		goto _A;
	}
}
//�����е���Ϣ��ʾ
void ShowAllInfo() {
	int choice;
	int Sum[Maxnum];  //��¼�ܷ�
	int B[Maxnum];    //��������ѧ��
	system("cls");
	if (count > 0) {		//��Ϣ��Ŀ����0��˵��������Ϣ
		printf("\n\n\t\t\t		����ȫ����ѧ����Ϣ,һ��%dλ\n\n", count);
		printf("���\tѧ��\t����\t�Ա�\t����\t��ͥסַ\t����\t��ѧ\tӢ��\t����\t��ѧ\t����\t�ܷ�\n");
		for (int i = 0;i < count;i++) {		//����ţ�����Ϣȫ����ʾ
			B[i] = info[i].Idnumber;
			Sum[i] = info[i].Score[0] + info[i].Score[1] + info[i].Score[2] + info[i].Score[3] + info[i].Score[4] + info[i].Score[5];
			printf("%d\t%d\t%s\t%s\t%d\t%-16s", info[i].Num, info[i].Idnumber, info[i].Name, info[i].Sex, info[i].Age, info[i].Hometown);
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5], Sum[i]);
		}
		while (1) {
			printf("\n\t\t\t		��������\n");
			printf("\t\t\t		1-���ܷ�����\n");
			printf("\t\t\t		2-��ѧ���������ٴ���ʾ\n");
			printf("\t\t\t		3-ֱ�ӷ������˵�\n");
			scanf("%d", &choice);
			if (choice == 1) {		//�Ƚ��ֽܷ��������ɸߵ���
				for (int i = 0;i < count;i++) {
					for (int j = 0;j < count - 1;j++) {
						if (Sum[j] < Sum[j + 1]) {
							int temp = Sum[j];
							Sum[j] = Sum[j + 1];
							Sum[j + 1] = temp;
						}
					}
				}
				system("cls");
				printf("\n\n\t\t\t		����ȫ����ѧ����Ϣ,�����ܷ�����,һ��%dλ\n\n", count);
				printf("����\tѧ��\t����\t�Ա�\t����\t��ͥסַ\t����\t��ѧ\tӢ��\t����\t��ѧ\t����\t�ܷ�\n");
				for (int i = 0;i < count;i++) {
					for (int j = 0;j < count;j++) {
						int sum = info[j].Score[0] + info[j].Score[1] + info[j].Score[2] + info[j].Score[3] + info[j].Score[4] + info[j].Score[5];
						if (Sum[i] == sum) {	//���ź�����ܷ���ԭ�����ܷ�ƥ�䣬����ʾ
							printf("%d\t%d\t%s\t%s\t%d\t%-16s", i + 1, info[j].Idnumber, info[j].Name, info[j].Sex, info[j].Age, info[j].Hometown);
							printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[j].Score[0], info[j].Score[1], info[j].Score[2], info[j].Score[3], info[j].Score[4], info[j].Score[5], sum);
						}
					}
				}
				system("pause");
				printf("\t\t\t		�����������˵�\n");
				system("pause");
				InputChoice();
			}
			else if (choice == 2) {
				for (int i = 0;i < count;i++) {	//��ѧ��ȡ����B[]�������������ɵ͵���
					for (int j = 0;j < count - 1;j++) {
						if (B[j] > B[j + 1]) {
							int temp = B[j];
							B[j] = B[j + 1];
							B[j + 1] = temp;
						}
					}
				}
				system("cls");
				printf("\n\n\t\t\t		����ȫ����ѧ����Ϣ,����ѧ������,һ��%dλ\n\n", count);
				printf("���\tѧ��\t����\t�Ա�\t����\t��ͥסַ\t����\t��ѧ\tӢ��\t����\t��ѧ\t����\t�ܷ�\n");
				for (int i = 0;i < count;i++) {
					for (int j = 0;j < count;j++) {
						if (B[i] == info[j].Idnumber) {	//���ź����ѧ����ԭ����ѧ��ƥ�䣬����ʾ
							printf("%d\t%d\t%s\t%s\t%d\t%-16s", i + 1, info[j].Idnumber, info[j].Name, info[j].Sex, info[j].Age, info[j].Hometown);
							printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[j].Score[0], info[j].Score[1], info[j].Score[2], info[j].Score[3], info[j].Score[4], info[j].Score[5], Sum[j]);
						}
					}
				}
				system("pause");
				printf("\t\t\t		�����������˵�\n");
				system("pause");
				InputChoice();
			}
			else if (choice == 3) {
				printf("\t\t\t		���ڷ������˵�\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		������1��2��3��\n");
				system("pause");
			}
		}
	}
	else {
		printf("\t\t\t		ϵͳ��û���κ���Ϣ��\n");
		system("pause");
		printf("\t\t\t		���ڷ������˵�\n");
		system("pause");
		InputChoice();
	}
}
//����ģ��
void Save() {
	FILE* fp1;
	FILE* fp2;
	if ((fp1 = fopen("StudentScore.txt", "w")) == NULL) {
		printf("\t\t\t		�޷����ļ���\n");
		exit(0);
	}
	for (int i = 0;i < count;i++) {
		fprintf(fp1, " %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Num, info[i].Idnumber, info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
	}
	if (fclose(fp1)) {
		printf("\t\t\t		�޷��ر��ļ���\n");
		exit(0);
	}
	//ѧ��������Ϣ�ļ�
	if ((fp2 = fopen("StudentInfo.txt", "w")) == NULL) {
		printf("\t\t\t		�޷����ļ���\n");
		exit(0);
	}
	for (int i = 0;i < count;i++) {
		fprintf(fp2, "%d\t%s\t%s\t%s\t%d\n", info[i].Idnumber, info[i].Name, info[i].Sex, info[i].Hometown, info[i].Age);
	}
	if (fclose(fp2)) {
		printf("\t\t\t		�޷��ر��ļ���\n");
		exit(0);
	}
}
//�ʺ�ģ�飬���ڿ�ʼ�ͽ���
void Greeting(int i) {	//���ݲ����������ֿ�ʼ�����
	if (i) {
		system("cls");
		printf("\n\n");
		printf("\t\t\t		��ӭʹ��ѧ����Ϣ����ϵͳ\n");
		system("pause");
	}
	else {
		printf("\n\n");
		printf("\t\t\t		�ڴ��ٴ�ʹ��ѧ����Ϣ����ϵͳ\n");
		system("pause");
		exit(0);
	}
}