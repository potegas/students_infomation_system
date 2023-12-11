#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <process.h>
#include <string.h>
#include <windows.h>
#define Maxnum 100 //存储的最大信息数目

#include <stdio.h>
struct node {
	int Num;            //记录序号
	int Idnumber;       //记录学号
	char Name[15];      //记录姓名
	char Sex[10];		//记录性别
	int Age;			//年龄
	char Hometown[15];  //记录家廷地址
	int Score[6];       //记录成绩,语数英物化生
	struct node* next;  //下一个结点
};
typedef struct node* Point;

Point Head = NULL;		//指向头

//函数声明
void InputChoice();
void AddInfo();
void DeleteInfo();
void ModifyInfo();
void SearchInfo();
void ShowAllInfo();
void Greeting(int);
void Save();
void LoadInfo();

//主函数
int main()
{
	LoadInfo();
	Greeting(1);
	InputChoice();  //此调用不会返回来
}
//将信息从文件载入链表
void InputChoice() {
	int choice;
_A:
	system("cls");
	printf("\n\n");
	printf("\t\t\t		主菜单\n\n");
	printf("\t\t\t		请选择你的操作:\n\n");
	printf("\t\t\t		1-添加一个学生信息\n");
	printf("\t\t\t		2-删除一个学生信息\n");
	printf("\t\t\t		3-修改一个学生信息\n");
	printf("\t\t\t		4-查找一个学生信息\n");
	printf("\t\t\t		5-显示全部学生信息\n");
	printf("\t\t\t		0-退出程序\n");
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
	case 0:Greeting(0);  //此函数调用为程序唯一出口
		break;
	}
	if (choice > 5) {
		printf("\t\t\t		请输入正确的数字！\n");
		system("pause");
		goto _A;
	}
}
//主菜单
void LoadInfo() {
	int t;  //在读取中需要略过某些数据
	FILE* fp1;
	FILE* fp2;
	Point temp;
	Point Now=Head;
	if ((fp2 = fopen("StudentInfo.txt", "r")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		system("pause");
		exit(0);
	}
	if ((fp1 = fopen("StudentScore.txt", "r")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		system("pause");
		exit(0);
	}
	temp = (Point)malloc(sizeof(struct node));
	while (fscanf(fp2, "%d\t%s\t%s\t%s\t%d", &(temp->Idnumber), temp->Name, temp->Sex, temp->Hometown, &(temp->Age))!=EOF) {
		fscanf(fp1, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", &(temp->Num), &t, &(temp->Score[0]), &(temp->Score[1]), &(temp->Score[2]), &(temp->Score[3]), &(temp->Score[4]), &(temp->Score[5]));
		temp->next = NULL;
		if (Head == NULL) {
			Head = temp;
			Now = Head;
		}
		else {
			Now->next = temp;
			Now = Now->next;
		}
		temp = (Point)malloc(sizeof(struct node));
	} 
	if (fclose(fp2)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
	if (fclose(fp1)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
}
//添加学生信息
void AddInfo() {
	int choice, N;
	Point temp;
	Point Now = Head;
	system("cls");
	printf("\n\n\t\t\t		正在执行添加操作，请您按要求输入\n\n");
		_A:
	printf("\t\t\t		请输入添加的学生信息的个数\n");
		scanf("%d", &N);
		if (N < 0) {
			printf("\t\t\t		请输入正数！\n");
			system("pause");
			goto _A;
		}
	for (int k = 0;k < N;k++) {
	_C:
		temp = (Point)malloc(sizeof(struct node));
		temp->next = NULL;
		printf("\t\t\t		已输入%d个学生的信息\n", k);
		printf("\t\t\t		请输入学生的学号、姓名、性别、年龄、家庭住址\n");
		scanf("%d %s %s %d %s", &(temp->Idnumber), temp->Name, temp->Sex, &(temp->Age), temp->Hometown);
		fflush(stdin);
		while(Now!=NULL) {		
			//用于检测是否已经存在  Now==NULL意味着在Tail的下一个
			if (temp->Idnumber ==Now->Idnumber) {
				printf("\t\t\t		已存在此人的信息！\n");
				_B:
					printf("\t\t\t		请问是否重新添加？\n");
					printf("\t\t\t		1-是 2-否，返回主菜单\n");
					scanf("%d", &choice);
					if (choice == 1) {
						goto _C;
					}
					else if (choice == 2) {
						printf("\t\t\t		正在返回主菜单\n");
						system("pause");
						InputChoice();
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
						goto _B;
					}	
			}
			Now = Now->next;
		}
		Now = Head;
		fflush(stdin);
		printf("\n\t\t\t		请输入该学生的各科成绩，请按语数英物化生的顺序输入\n");
		scanf("%d %d %d %d %d %d", &(temp->Score[0]), &(temp->Score[1]), &(temp->Score[2]), &(temp->Score[3]), &(temp->Score[4]), &(temp->Score[5]));
		if (Head == NULL) {
			Head = temp;
			Now = Head;
			Now->Num = 1;
		}
		else {
			int h = 2;
			while (Now->next != NULL) {
				Now = Now->next;
				h++;
			}
			temp->Num = h;
			Now->next = temp;
		}
	}
	Save();			//将新添加的信息保存到文件中
	printf("\t\t\t		添加成功！\n");
	system("pause");
	printf("\t\t\t		正在返回主菜单！\n");
	system("pause");
	InputChoice();
}
//删除某个学生的信息
void DeleteInfo() {
	Point Now = Head;
	Point Last=Head;
	char NAME[15];
	int way, ID, choice;  //Check用于判断是否存在此人的信息，0表示不存在;Mark用于标记所删除的信息的下标
	system("cls");
	printf("\n\n\t\t\t		正在执行删除操作，请您按要求输入\n\n");
	if (Now == NULL) {
		printf("\t\t\t		目前系统中没有任何信息！\n");
		system("pause");
		printf("\t\t\t		正在返回主菜单\n");
		system("pause");
		InputChoice();
	}
_A:
	printf("\t\t\t		请使用：\n");
	printf("\t\t\t		1-学号或2-姓名 选择对象\n");
	printf("\t\t\t		3-回到主菜单\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		请输入操作对象的学号:\n");
		scanf("%d", &ID);
		while (Now != NULL) {
			if (Now->Idnumber == ID) {
				
				break;
			}
			Last = Now;
			Now = Now->next;
		}
		if (Now == NULL) {
			printf("\t\t\t		不存在此人的信息！\n");
			system("pause");
			_B:
				printf("\t\t\t		是否重新输入 1-重新输入 2-返回主菜单\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		重新输入请输入1或2！\n");
				system("pause");
				goto _B;
			}

		}
		else {
		_B1:
			printf("\t\t\t		是否确定删除学号为%d的学生的信息？\n", ID);
			printf("\t\t\t		1-是 2-否，返回重新输入 3-否，返回主菜单\n");
			scanf("%d", &choice);
			if (choice == 1) {
				Last->next = Now->next;
				free(Now);
				Save();
				printf("\t\t\t		已成功删除学号为%d的学生的信息！\n", ID);
				system("pause");
				printf("\t\t\t		即将返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else if (choice == 2) {
				goto _A;
			}
			else if (choice == 3) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		请输入1、2或3！\n");
				system("pause");
				goto _B1;
			}

		}
	}
	else if (way == 2) {
		printf("\t\t\t		请输入操作对象的姓名:\n");
		scanf("%s", NAME);
		while(Now!=NULL) {
			if (strcmp(NAME, Now->Name) == 0) {
				break;
			}
			Last = Now;
			Now = Now->next;
		}
		if (Now==NULL) {
			printf("\t\t\t		不存在此人的信息！\n");
			system("pause");
			_C:
				printf("\t\t\t		是否重新输入 1-重新输入 2-返回主菜单\n");
				scanf("%d", &choice);
				if (choice == 1) {
					goto _A;
				}
				else if (choice == 2) {
					printf("\t\t\t		正在返回主菜单\n");
					system("pause");
					InputChoice();
				}
				else {
					printf("\t\t\t		重新输入请输入1或2！\n");
					system("pause");
					goto _C;
				}
			
		}
		else {
			_C1:
				printf("\t\t\t		是否确定删除姓名为%s的学生的信息?\n", NAME);
				printf("\t\t\t		1-是 2-否，返回重新输入 3-否，返回主菜单\n");
				scanf("%d", &choice);
				if (choice == 1) {
					Last->next = Now->next;
					free(Now);
					Save();
					printf("\t\t\t		已成功删除姓名为%s的学生的信息！\n", NAME);
					system("pause");
					printf("\t\t\t		即将返回主菜单\n");
					system("pause");
					InputChoice();
				}
				else if (choice == 2) {
					goto _A;
				}
				else if (choice == 3) {
					printf("\t\t\t		正在返回主菜单\n");
					system("pause");
					InputChoice();
				}
				else {
					printf("\t\t\t		请输入1、2或3！\n");
					system("pause");
					goto _C1;
				}
		}
	}
	else if (way == 3) {
		printf("\t\t\t		正在返回主菜单\n");
		system("pause");
		InputChoice();
	}
	else {
		printf("\t\t\t		请输入1、2或3！\n");
		system("pause");
		goto _A;
	}
}
//修改某个学生的信息
void ModifyInfo() {
	int choice, ID, way, choice1;
	Point Now=Head;
	char NAME[15];
	system("cls");
	printf("\n\n\t\t\t		正在执行修改操作，请您按要求输入\n\n");
	if (Now == NULL) {
		printf("\t\t\t		目前系统中没有任何信息！\n");
		system("pause");
		printf("\t\t\t		正在返回主菜单\n");
		system("pause");
		InputChoice();
	}
_A:
	printf("\t\t\t		请使用：\n");
	printf("\t\t\t		1-学号或2-姓名 选择对象\n");
	printf("\t\t\t		3-回到主菜单\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		请输入操作对象的学号:\n");
		scanf("%d", &ID);
		while(Now!=NULL) {
			if (ID == Now->Idnumber) {
				printf("\t\t\t		请输入需要修改的信息\n");
				printf("\t\t\t		1-学号 2-姓名 3-性别 4-年龄 5-家庭住址 6-各科成绩\n");  //学号不能够重复
			_B:
				scanf("%d", &choice);
				Point NOW = Head;
				switch (choice) {		//用于分别修改各个信息
				case 1:
						int tempID;
						printf("\t\t\t		请输入新的学号\n");
						scanf("%d", &tempID);
						//用于检测学号是否重复
						while(NOW!=NULL) {  
							if (NOW->Idnumber == tempID) {
								printf("\t\t\t		已存在此学号！\n");
								_D:
									printf("\t\t\t		请问是否重新添加？\n");
									printf("\t\t\t		1-是 2-否，返回主菜单\n");
									scanf("%d", &choice);
									if (choice == 1) {
										printf("\t\t\t		请再次输入学号\n");
										goto _B;
									}
									else if (choice == 2) {
										printf("\t\t\t		正在返回主菜单\n");
										system("pause");
										InputChoice();
									}
									else {
										printf("\t\t\t		请输入1或2！\n");
										system("pause");
										goto _D;
									}
							}
							NOW = NOW->next;
						}
						_D1:
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							printf("\t\t\t		已将学号为%d的学生的学号更改为%d\n",Now->Idnumber, tempID);
							Now->Idnumber = tempID;
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
							goto _D1;
						}
				case 2:
						char tempNAME[15];
						printf("\t\t\t		请输入新的姓名\n");
						scanf("%s", tempNAME);
					_D2:
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(Now->Name, tempNAME);
							printf("\t\t\t		已将学号为%d的学生的姓名更改为%s\n", Now->Idnumber, Now->Name);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
							goto _D2;
						}
				case 3:
						char tempSEX[10];
						printf("\t\t\t		请输入新的性别\n");
						scanf("%s", tempSEX);
						_D3:
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(Now->Sex, tempSEX);
							printf("\t\t\t		已将学号为%d的学生的性别更改为%s\n", Now->Idnumber, Now->Sex);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
							goto _D3;
						}
				case 4:
						int tempAGE;
						printf("\t\t\t		请输入新的年龄\n");
						scanf("%d", &tempAGE);
						_D4:
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							Now->Age = tempAGE;
							printf("\t\t\t		已将学号为%d的学生的年龄更改为%d\n", Now->Idnumber, Now->Age);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
							goto _D4;
						}
				case 5:
						char tempHOME[15];
						printf("\t\t\t		请输入新的家庭住址\n");
						scanf("%s", tempHOME);
						_D5:
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(Now->Hometown, tempHOME);
							printf("\t\t\t		已将学号为%d的学生的家庭住址更改为%s\n", Now->Idnumber, Now->Hometown);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
							goto _D5;
						}
				case 6:
						int SCORE[6];
						printf("\t\t\t		请输入新的各科成绩\n");
						printf("\t\t\t		请以语数英物化生的顺序输入\n");
						for (int j = 0;j < 6;j++) {
							scanf("%d", &SCORE[j]);
						}
						_D6:
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							for (int j = 0;j < 6;j++) {
								Now->Score[j] = SCORE[j];
							}
							printf("\t\t\t		已将学号为%d的学生的语数英物化生成绩更改为%d %d %d %d %d %d\n", Now->Idnumber, Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5]);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
							goto _D6;
						}
				}
				Save();
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			Now = Now->next;
		}	//当跑完了for还是没有找到目标，才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		_B1:
			printf("\t\t\t		是否重新输入？1-重新输入 2-返回主菜单\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		重新输入请输入1或2！\n");
				system("pause");
				goto _B1;
			}
		
	}
	else if (way == 2) {
		printf("\t\t\t		请输入操作对象的姓名:\n");
		scanf("%s", NAME);
		while(Now!=NULL) {
			if ((strcmp(NAME, Now->Name)) == 0) {
				printf("\t\t\t		请输入需要修改的信息\n");
				printf("\t\t\t		1-学号 2-姓名 3-性别 4-年龄 5-家庭住址 6-各科成绩\n");  //学号不能够重复
			_C:
				scanf("%d", &choice);
				Point NOW = Head;
				switch (choice) {		//用于分别修改各个信息
				case 1:
					int tempID;
					printf("\t\t\t		请输入新的学号\n");
					scanf("%d", &tempID);
					while(NOW!=NULL) {  //用于检测学号是否重复
						if (NOW->Idnumber == tempID) {
							printf("\t\t\t		已存在此学号！\n");
						_F:
							printf("\t\t\t		请问是否重新添加？\n");
							printf("\t\t\t		1-是 2-否，返回主菜单\n");
							scanf("%d", &choice);
							if (choice == 1) {
								printf("\t\t\t		请再次输入学号\n");
								goto _C;
							}
							else if (choice == 2) {
								printf("\t\t\t		正在返回主菜单\n");
								system("pause");
								InputChoice();
							}
							else {
								printf("\t\t\t		请输入1或2！\n");
								system("pause");
								goto _F;
							}
						}
						NOW = NOW->next;
					}
				_F1:
					printf("\t\t\t		是否确定更改？1-是 2-否\n");
					scanf("%d", &choice1);
					if (choice1 == 1) {
						printf("\t\t\t		已将姓名为%s的学生的学号更改为%d\n", Now->Name, tempID);
						Now->Idnumber = tempID;
						system("pause");
						break;
					}
					else if (choice == 2) {
						goto _A;
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
						goto _F1;
					}
				case 2:
					char tempNAME[15];
					printf("\t\t\t		请输入新的姓名\n");
					scanf("%s", tempNAME);
				_F2:
					printf("\t\t\t		是否确定更改？1-是 2-否\n");
					scanf("%d", &choice1);
					if (choice1 == 1) {
						strcpy(Now->Name, tempNAME);
						printf("\t\t\t		已将姓名为%s的学生的姓名更改为%s\n", Now->Name, Now->Name);
						system("pause");
						break;
					}
					else if (choice == 2) {
						goto _A;
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
						goto _F2;
					}
				case 3:
					char tempSEX[10];
					printf("\t\t\t		请输入新的性别\n");
					scanf("%s", tempSEX);
				_F3:
					printf("\t\t\t		是否确定更改？1-是 2-否\n");
					scanf("%d", &choice1);
					if (choice1 == 1) {
						strcpy(Now->Sex, tempSEX);
						printf("\t\t\t		已将姓名为%s的学生的性别更改为%s\n", Now->Name, Now->Sex);
						system("pause");
						break;
					}
					else if (choice == 2) {
						goto _A;
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
						goto _F3;
					}
				case 4:
					int tempAGE;
					printf("\t\t\t		请输入新的年龄\n");
					scanf("%d", &tempAGE);
				_F4:
					printf("\t\t\t		是否确定更改？1-是 2-否\n");
					scanf("%d", &choice1);
					if (choice1 == 1) {
						Now->Age = tempAGE;
						printf("\t\t\t		已将姓名为%s的学生的年龄更改为%d\n", Now->Name, Now->Age);
						system("pause");
						break;
					}
					else if (choice == 2) {
						goto _A;
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
						goto _F4;
					}
				case 5:
					char tempHOME[15];
					printf("\t\t\t		请输入新的家庭住址\n");
					scanf("%s", tempHOME);
				_F5:
					printf("\t\t\t		是否确定更改？1-是 2-否\n");
					scanf("%d", &choice1);
					if (choice1 == 1) {
						strcpy(Now->Hometown, tempHOME);
						printf("\t\t\t		已将姓名为%s的学生的家庭住址更改为%s\n", Now->Name, Now->Hometown);
						system("pause");
						break;
					}
					else if (choice == 2) {
						goto _A;
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
						goto _F5;
					}
				case 6:
					int SCORE[6];
					printf("\t\t\t		请输入新的各科成绩\n");
					printf("\t\t\t		请以语数英物化生的顺序输入\n");
					for (int j = 0;j < 6;j++) {
						scanf("%d", &SCORE[j]);
					}
				_F6:
					printf("\t\t\t		是否确定更改？1-是 2-否\n");
					scanf("%d", &choice1);
					if (choice1 == 1) {
						for (int j = 0;j < 6;j++) {
							Now->Score[j] = SCORE[j];
						}
						printf("\t\t\t		已将姓名为%s的学生的语数英物化生成绩更改为%d %d %d %d %d %d\n", Now->Name, Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5]);
						system("pause");
						break;
					}
					else if (choice == 2) {
						goto _A;
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
						goto _F6;
					}
				}
				Save();
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			Now = Now->next;
		}	//当未找到目标才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		_C1:
			printf("\t\t\t		是否重新输入？1-重新输入 2-返回主菜单\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		重新输入请输入1或2！\n");
				system("pause");
				goto _C1;
			}
		
	}
	else if (way == 3) {
		printf("\t\t\t		正在返回主菜单\n");
		system("pause");
		InputChoice();
	}
	else {
		printf("\t\t\t		请输入1、2或3！\n");
		system("pause");
		goto _A;
	}
}
//查找某个学生的信息
void SearchInfo() {
	Point Now = Head;
	int way, ID, choice;
	char NAME[15];
	system("cls");
	printf("\n\n\t\t\t		正在执行查找操作，请您按要求输入\n\n");
	if (Now == NULL) {
		printf("\t\t\t		目前系统中没有任何信息！\n");
		system("pause");
		printf("\t\t\t		正在返回主菜单\n");
		system("pause");
		InputChoice();
	}
_A:
	printf("\t\t\t		请使用：\n");
	printf("\t\t\t		1-学号或2-姓名 选择对象\n");
	printf("\t\t\t		3-回到主菜单\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		请输入操作对象的学号:\n");
		scanf("%d", &ID);
		while(Now!=NULL) {
			if (ID == Now->Idnumber) {
				printf("\t\t\t		学号为%d该学生的信息为：\n", Now->Idnumber);
				printf("\t\t\t		姓名\t性别\t年龄\t住址\n");
				printf("\t\t\t		%s\t%s\t%d\t%s\n", Now->Name, Now->Sex, Now->Age, Now->Hometown);
				printf("\n\t\t\t		学号%d的学生的成绩为：\n", Now->Idnumber);
				printf("\t\t\t		语文\t数学\t英语\t物理\t化学\t生物\n");
				printf("\t\t\t		%d\t%d\t%d\t%d\t%d\t%d\n", Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5]);
				system("pause");
				printf("\t\t\t		即将返回主菜单\n");
				system("pause");
				InputChoice();
			}
			Now = Now->next;
		}	//未找到目标才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		_B:
			printf("\t\t\t		是否重新输入？1-重新输入 2-返回主菜单\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		重新输入请输入1或2！\n");
				system("pause");
				goto _B;
			}
		
	}
	else if (way == 2) {
		printf("\t\t\t		请输入操作对象的姓名:\n");
		scanf("%s", NAME);
		while(Now!=NULL) {
			if ((strcmp(NAME, Now->Name)) == 0) {
				printf("\t\t\t		姓名为%s该学生的信息为：\n", Now->Name);
				printf("\t\t\t		学号\t性别\t年龄\t住址\n");
				printf("\t\t\t		%d\t%s\t%d\t%s\n", Now->Idnumber, Now->Sex, Now->Age, Now->Hometown);
				printf("\n\t\t\t		姓名为%s的学生的成绩为：\n", Now->Name);
				printf("\t\t\t		语文\t数学\t英语\t物理\t化学\t生物\n");
				printf("\t\t\t		%d\t%d\t%d\t%d\t%d\t%d\n", Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5]);
				system("pause");
				printf("\t\t\t		即将返回主菜单\n");
				system("pause");
				InputChoice();
			}
			Now = Now->next;
		}
		//未找到目标才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		_B1:
			printf("\t\t\t		是否重新输入？1-重新输入 2-返回主菜单\n");
			scanf("%d", &choice);
			if (choice == 1) {
				goto _A;
			}
			else if (choice == 2) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		重新输入请输入1或2！\n");
				system("pause");
				goto _B1;
			}
	}
	else if (way == 3) {
		printf("\t\t\t		正在返回主菜单\n");
		system("pause");
		InputChoice();
	}
	else {
		printf("\t\t\t		请输入1、2或3！\n");
		system("pause");
		goto _A;
	}
}
//将所有的信息显示
void ShowAllInfo() {
	Point Now = Head;
	int choice;
	int Sum[Maxnum];  //记录总分
	int B[Maxnum];    //辅助排序学号
	int count=0;
	system("cls");
	while (Now != NULL) {
		count++;
		Now = Now->next;
	}
	Now = Head;
	if (Head!=NULL) {		
		printf("\n\n\t\t\t		这是全部的学生信息,一共%d位\n\n", count);
		printf("序号\t学号\t姓名\t性别\t年龄\t家庭住址\t语文\t数学\t英语\t物理\t化学\t生物\t总分\n");
		int p = 0;
		while(Now!=NULL) {		//将序号，和信息全部显示
			B[p] = Now->Idnumber;
			Sum[p] = Now->Score[0] + Now->Score[1] + Now->Score[2] + Now->Score[3] + Now->Score[4] + Now->Score[5];
			printf("%d\t%d\t%s\t%s\t%d\t%-16s",Now->Num, Now->Idnumber, Now->Name, Now->Sex, Now->Age, Now->Hometown);
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5], Sum[p]);
			Now = Now->next;
			p++;
		}
		Now = Head;
		_A:
			printf("\n\t\t\t		可以输入1或2来再次显示\n");
			printf("\t\t\t		1-按总分排序\n");
			printf("\t\t\t		2-按学号排序\n");
			printf("\t\t\t		3-直接返回主菜单\n");
			scanf("%d", &choice);
			if (choice == 1) {		//先将总分进行排序，由高到低
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
				printf("\n\n\t\t\t		这是全部的学生信息,按照总分排序,一共%d位\n\n", count);
				printf("排名\t学号\t姓名\t性别\t年龄\t家庭住址\t语文\t数学\t英语\t物理\t化学\t生物\t总分\n");
				int sum = -1;
				for (int i = 0;i < count;i++) {
					while(Now!=NULL) {
						if (sum == Sum[i]) {		//如果当前Sum[]与上一个sum相同，跳过这个人，因为上一轮已经显示
							Now = Now->next;
						}
						sum = Now->Score[0] + Now->Score[1] + Now->Score[2] + Now->Score[3] + Now->Score[4] + Now->Score[5];
						if (Sum[i] == sum) {	//将排好序的总分与原来的总分匹配，并显示
							printf("%d\t%d\t%s\t%s\t%d\t%-16s", i + 1, Now->Idnumber, Now->Name, Now->Sex, Now->Age, Now->Hometown);
							printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5], sum);
							break;
						}
						Now = Now->next;
					}
					Now = Head;
				}
				system("pause");
				goto _A;
			}
			else if (choice == 2) {
				for (int i = 0;i < count;i++) {	//将学号取出到B[]，并进行排序，由低到高
					for (int j = 0;j < count - 1;j++) {
						if (B[j] > B[j + 1]) {
							int temp = B[j];
							B[j] = B[j + 1];
							B[j + 1] = temp;
						}
					}
				}
				system("cls");
				printf("\n\n\t\t\t		这是全部的学生信息,按照学号排序,一共%d位\n\n", count);
				printf("序号\t学号\t姓名\t性别\t年龄\t家庭住址\t语文\t数学\t英语\t物理\t化学\t生物\t总分\n");
				for (int i = 0;i < count;i++) {
					while(Now!=NULL) {
						if (B[i] == Now->Idnumber) {	//将排好序的学号与原来的学号匹配，并显示
							printf("%d\t%d\t%s\t%s\t%d\t%-16s", i + 1, Now->Idnumber, Now->Name, Now->Sex, Now->Age, Now->Hometown);
							printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5], Sum[i]);
						}
						Now = Now->next;
					}
					Now = Head;
				}
				system("pause");
				goto _A;
			}
			else if (choice == 3) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		请输入1、2或3！\n");
				system("pause");
				goto _A;
			}
		
	}
	else {
		printf("\n\n\t\t\t		目前系统中没有任何信息！\n");
		system("pause");
		printf("\t\t\t		正在返回主菜单\n");
		system("pause");
		InputChoice();
	}
}
//保存模块
void Save() {
	FILE* fp1;
	FILE* fp2;
	Point Now=Head;
	if ((fp1 = fopen("StudentScore.txt", "w")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		system("pause");
		exit(0);
	}if ((fp2 = fopen("StudentInfo.txt", "w")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		system("pause");
		exit(0);
	}
	while(Now!=NULL){
		fprintf(fp1, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", Now->Num, Now->Idnumber, Now->Score[0], Now->Score[1], Now->Score[2], Now->Score[3], Now->Score[4], Now->Score[5]);
		fprintf(fp2, "%d\t%s\t%s\t%s\t%d\n", Now->Idnumber, Now->Name, Now->Sex, Now->Hometown, Now->Age);
		Now = Now->next;
	}
	if (fclose(fp1)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
		
	if (fclose(fp2)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
}
//问候模块，开始与结束
void Greeting(int i) {	//传递参数用于区分开始与结束
	if (i) {
		system("cls");
		printf("\n\n");
		printf("\t\t\t		欢迎使用学生信息管理系统\n");
		system("pause");
	}
	else {
		printf("\n\n");
		printf("\t\t\t		期待再次使用学生信息管理系统\n");
		system("pause");
		exit(0);
	}
}

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
