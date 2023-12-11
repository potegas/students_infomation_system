#include <stdio.h>
#include <process.h>
#include <string.h>
#include <windows.h>
#define Maxnum 100 //存储的最大信息数目

//结构数组，用于存储所有的信息
struct student {
	int Num;            //记录序号
	int Idnumber;       //记录学号
	char Name[15];      //记录姓名
	char Sex[10];		//记录性别
	int Age;			//年龄
	char Hometown[15];  //记录家廷地址
	int Score[6];       //记录成绩,语数英物化生
} info[Maxnum];

int count; //全局变量，记录了一共有多少个信息数目  实际上有count+1个数据

//函数声明
void InputChoice();
void AddInfo();
void DeleteInfo();
void ModifyInfo();
void SearchInfo();
void ShowAllInfo();
void Greeting(int);
void Save();

//主函数
int	main() {
	FILE* fp1;
	FILE* fp2;
	//将文件里的信息内容读取到结构数组中
	//先读取学生基本信息
	if ((fp2 = fopen("StudentInfo.txt", "r")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		exit(0);
	}
	while (fscanf(fp2, "%d\t%s\t%s\t%s\t%d", &info[count].Idnumber, info[count].Name, info[count].Sex, info[count].Hometown, &info[count].Age) != EOF) {
		count++;
	}
	if (fclose(fp2)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
	//再读取学生成绩信息
	int t;	//在读取中需要略过某些数据
	count = 0;
	if ((fp1 = fopen("StudentScore.txt", "r")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		exit(0);
	}
	while (fscanf(fp1, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", &info[count].Num, &t, &info[count].Score[0], &info[count].Score[1], &info[count].Score[2], &info[count].Score[3], &info[count].Score[4], &info[count].Score[5]) != EOF) {
		count++;	//获取了信息数目
	}
	if (fclose(fp1)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
	Greeting(1);
	InputChoice();  //此调用不会返回来
}
//主菜单
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
//添加学生信息
void AddInfo() {
	int choice, N;
	system("cls");
	printf("\n\n\t\t\t		正在执行添加操作，请您按要求输入\n\n");
	while (1) {
		printf("\t\t\t		请输入添加的学生信息的个数\n");
		scanf("%d", &N);
		if (N > 0) {
			break;
		}
		else {
			printf("\t\t\t		请输入正数！\n");
			system("pause");
		}
	}
	for (int k = 0;k < N;k++) {
	_Again:
		printf("\t\t\t		已输入%d个学生的信息\n", k);
		printf("\t\t\t		请输入学生的学号、姓名、性别、年龄、家庭住址\n");
		scanf("%d %s %s %d %s", &info[count].Idnumber, info[count].Name, info[count].Sex, &info[count].Age, info[count].Hometown);
		fflush(stdin);
		for (int i = 0;i < count;i++) {		//用于检测是否已经存在
			if (info[i].Idnumber == info[count].Idnumber) {
				printf("\t\t\t		已存在此人的信息！\n");
				while (1) {
					printf("\t\t\t		请问是否重新添加？\n");
					printf("\t\t\t		1-是 2-否，返回主菜单\n");
					scanf("%d", &choice);
					if (choice == 1) {
						goto _Again;
					}
					else if (choice == 2) {
						printf("\t\t\t		正在返回主菜单\n");
						system("pause");
						InputChoice();
					}
					else {
						printf("\t\t\t		请输入1或2！\n");
						system("pause");
					}
				}
			}
		}
		fflush(stdin);
		printf("\n\t\t\t		请输入该学生的各科成绩，请按语数英物化生的顺序输入\n");
		scanf("%d %d %d %d %d %d", &info[count].Score[0], &info[count].Score[1], &info[count].Score[2], &info[count].Score[3], &info[count].Score[4], &info[count].Score[5]);
		info[count].Num = info[count - 1].Num + 1;
		count++;  //所保存的信息数目加一
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
	char NAME[15];
	int way, ID, choice, Check = 0, Mark;  //Check用于判断是否存在此人的信息，0表示不存在;Mark用于标记所删除的信息的下标
	system("cls");
	printf("\n\n\t\t\t		正在执行删除操作，请您按要求输入\n\n");
_A:
	printf("\t\t\t		请使用：\n");
	printf("\t\t\t		1-学号或2-姓名 选择对象\n");
	printf("\t\t\t		3-回到主菜单\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		请输入操作对象的学号:\n");
		scanf("%d", &ID);
		for (int i = 0;i < count;i++) {
			if (info[i].Idnumber == ID) {
				Check = 1;  //表示存在此人的信息
				Mark = i;
			}
		}
		if (Check == 0) {
			printf("\t\t\t		不存在此人的信息！\n");
			system("pause");
			while (1) {
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
				}
			}
		}
		else if (Check == 1) {
			while (1) {		//询问是否确定删除
				printf("\t\t\t		是否确定删除学号为%d的学生的信息？\n", ID);
				printf("\t\t\t		1-是 2-否，返回重新输入 3-否，返回主菜单\n");
				scanf("%d", &choice);
				if (choice == 1) {
					for (int i = Mark;i < count - Mark - 1;i++) {	//将所有的信息都往前移动一位，除了序号
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
					count--;		//将信息数目减一
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
				}
			}
		}
	}
	else if (way == 2) {
		printf("\t\t\t		请输入操作对象的姓名:\n");
		scanf("%s", NAME);
		for (int i = 0;i <= count;i++) {
			if (strcmp(NAME, info[i].Name) == 0) {
				Check = 1;  //表示存在此人的信息
				Mark = i;
			}
		}
		if (Check == 0) {
			printf("\t\t\t		不存在此人的信息！\n");
			system("pause");
			while (1) {
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
				}
			}
		}
		else {
			while (1) {
				printf("\t\t\t		是否确定删除姓名为%s的学生的信息?\n", NAME);
				printf("\t\t\t		1-是 2-否，返回重新输入 3-否，返回主菜单\n");
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
				}
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
	char NAME[15];
	system("cls");
	printf("\n\n\t\t\t		正在执行修改操作，请您按要求输入\n\n");
_A:
	printf("\t\t\t		请使用：\n");
	printf("\t\t\t		1-学号或2-姓名 选择对象\n");
	printf("\t\t\t		3-回到主菜单\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		请输入操作对象的学号:\n");
		scanf("%d", &ID);
		for (int i = 0;i < count;i++) {
			if (ID == info[i].Idnumber) {
				printf("\t\t\t		请输入需要修改的信息\n");
				printf("\t\t\t		1-学号 2-姓名 3-性别 4-年龄 5-家庭住址 6-各科成绩\n");  //学号不能够重复
			_B:
				scanf("%d", &choice);
				switch (choice) {		//用于分别修改各个信息
				case 1:
					while (1) {
						int tempID;
						printf("\t\t\t		请输入新的学号\n");
						scanf("%d", &tempID);
						for (int j = 0;j < count;j++) {  //用于检测学号是否重复
							if (info[j].Idnumber == tempID) {
								printf("\t\t\t		已存在此学号！\n");
								while (1) {
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
									}
								}
							}
						}
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							printf("\t\t\t		已将学号为%d的学生的学号更改为%d\n", info[i].Idnumber, tempID);
							info[i].Idnumber = tempID;
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 2:
					while (1) {
						char tempNAME[15];
						printf("\t\t\t		请输入新的姓名\n");
						scanf("%s", tempNAME);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Name, tempNAME);
							printf("\t\t\t		已将学号为%d的学生的姓名更改为%s\n", info[i].Idnumber, info[i].Name);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 3:
					while (1) {
						char tempSEX[10];
						printf("\t\t\t		请输入新的性别\n");
						scanf("%s", tempSEX);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Sex, tempSEX);
							printf("\t\t\t		已将学号为%d的学生的性别更改为%s\n", info[i].Idnumber, info[i].Sex);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 4:
					while (1) {
						int tempAGE;
						printf("\t\t\t		请输入新的年龄\n");
						scanf("%d", &tempAGE);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							info[i].Age = tempAGE;
							printf("\t\t\t		已将学号为%d的学生的年龄更改为%d\n", info[i].Idnumber, info[i].Age);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 5:
					while (1) {
						char tempHOME[15];
						printf("\t\t\t		请输入新的家庭住址\n");
						scanf("%s", tempHOME);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Hometown, tempHOME);
							printf("\t\t\t		已将学号为%d的学生的家庭住址更改为%s\n", info[i].Idnumber, info[i].Hometown);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 6:
					while (1) {
						int SCORE[6];
						printf("\t\t\t		请输入新的各科成绩\n");
						printf("\t\t\t		请以语数英物化生的顺序输入\n");
						for (int j = 0;j < 6;j++) {
							scanf("%d", &SCORE[j]);
						}
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							for (int j = 0;j < 6;j++) {
								info[i].Score[j] = SCORE[j];
							}
							printf("\t\t\t		已将学号为%d的学生的语数英物化生成绩更改为%d %d %d %d %d %d\n", info[i].Idnumber, info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				}
				Save();
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
		}	//当跑完了for还是没有找到目标，才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		while (1) {
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
			}
		}
	}
	else if (way == 2) {
		printf("\t\t\t		请输入操作对象的姓名:\n");
		scanf("%s", NAME);
		for (int i = 0;i < count;i++) {
			if ((strcmp(NAME, info[i].Name)) == 0) {
				printf("\t\t\t		请输入需要修改的信息\n");
				printf("\t\t\t		1-学号 2-姓名 3-性别 4-年龄 5-家庭住址 6-各科成绩\n");
			_C:
				scanf("%d", &choice);
				switch (choice) {		//分别修改
				case 1:
					while (1) {
						int tempID;
						printf("\t\t\t		请输入新的学号\n");
						scanf("%d", &tempID);
						for (int j = 0;j < count;j++) {  //用于检测学号是否重复
							if (info[j].Idnumber == tempID) {
								printf("\t\t\t		已存在此学号！\n");
								while (1) {
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
									}
								}
							}
						}
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							info[i].Idnumber = tempID;
							printf("\t\t\t		已将姓名为%s的学生的学号更改为%d\n", info[i].Name, info[i].Idnumber);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 2:
					while (1) {
						char tempNAME[15];
						printf("\t\t\t		请输入新的姓名\n");
						scanf("%s", tempNAME);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							printf("\t\t\t		已将姓名为%s的学生的姓名更改为%s\n", info[i].Name, tempNAME);
							strcpy(info[i].Name, tempNAME);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 3:
					while (1) {
						char tempSEX[10];
						printf("\t\t\t		请输入新的性别\n");
						scanf("%s", tempSEX);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Sex, tempSEX);
							printf("\t\t\t		已将姓名为%s的学生的性别更改为%s\n", info[i].Name, info[i].Sex);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 4:
					while (1) {
						int tempAGE;
						printf("\t\t\t		请输入新的年龄\n");
						scanf("%d", &tempAGE);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							info[i].Age = tempAGE;
							printf("\t\t\t		已将姓名为%s的学生的年龄更改为%d\n", info[i].Name, info[i].Age);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 5:
					while (1) {
						char tempHOME[15];
						printf("\t\t\t		请输入新的家庭住址\n");
						scanf("%s", tempHOME);
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							strcpy(info[i].Hometown, tempHOME);
							printf("\t\t\t		已将姓名为%s的学生的家庭住址更改为%s\n", info[i].Name, info[i].Hometown);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				case 6:
					while (1) {
						int SCORE[6];
						printf("\t\t\t		请输入新的各科成绩\n");
						printf("\t\t\t		请以语数英物化生的顺序输入\n");
						for (int j = 0;j < 6;j++) {
							scanf("%d", &SCORE[j]);
						}
						printf("\t\t\t		是否确定更改？1-是 2-否\n");
						scanf("%d", &choice1);
						if (choice1 == 1) {
							for (int j = 0;j < 6;j++) {
								info[i].Score[j] = SCORE[j];
							}
							printf("\t\t\t		已将姓名为%s的学生的语数英物化生成绩更改为%d %d %d %d %d %d\n", info[i].Name, info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
							system("pause");
							break;
						}
						else if (choice == 2) {
							goto _A;
						}
						else {
							printf("\t\t\t		请输入1或2！\n");
							system("pause");
						}
					}break;
				}
				Save();
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
		}	//当未找到目标才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		while (1) {
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
//查找某个学生的信息
void SearchInfo() {
	int way, ID, choice;
	char NAME[15];
	system("cls");
	printf("\n\n\t\t\t		正在执行查找操作，请您按要求输入\n\n");
_A:
	printf("\t\t\t		请使用：\n");
	printf("\t\t\t		1-学号或2-姓名 选择对象\n");
	printf("\t\t\t		3-回到主菜单\n");
	scanf("%d", &way);
	if (way == 1) {
		printf("\t\t\t		请输入操作对象的学号:\n");
		scanf("%d", &ID);
		for (int i = 0;i < count;i++) {
			if (ID == info[i].Idnumber) {
				printf("\t\t\t		学号%d该学生的信息为：\n", info[i].Idnumber);
				printf("\t\t\t		姓名\t性别\t年龄\t住址\n");
				printf("\t\t\t		%s\t%s\t%d\t%s\n", info[i].Name, info[i].Sex, info[i].Age, info[i].Hometown);
				printf("\n\t\t\t		学号%d的学生的成绩为：\n", info[i].Idnumber);
				printf("\t\t\t		语文\t数学\t英语\t物理\t化学\t生物\n");
				printf("\t\t\t		%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
				system("pause");
				printf("\t\t\t		即将返回主菜单\n");
				system("pause");
				InputChoice();
			}
		}	//未找到目标才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		while (1) {
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
			}
		}
	}
	else if (way == 2) {
		printf("\t\t\t		请输入操作对象的姓名:\n");
		scanf("%s", NAME);
		for (int i = 0;i < count;i++) {
			if ((strcmp(NAME, info[i].Name)) == 0) {
				printf("\t\t\t		姓名为%s该学生的信息为：\n", info[i].Name);
				printf("\t\t\t		学号\t性别\t年龄\t住址\n");
				printf("\t\t\t		%d\t%s\t%d\t%s\n", info[i].Idnumber, info[i].Sex, info[i].Age, info[i].Hometown);
				printf("\n\t\t\t		姓名为%s的学生的成绩为：\n", info[i].Name);
				printf("\t\t\t		语文\t数学\t英语\t物理\t化学\t生物\n");
				printf("\t\t\t		%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
				system("pause");
				printf("\t\t\t		即将返回主菜单\n");
				system("pause");
			}
		}InputChoice();
		//未找到目标才会执行以下代码
		printf("\t\t\t		不存在此人的信息！\n");
		system("pause");
		while (1) {
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
//将所有的信息显示
void ShowAllInfo() {
	int choice;
	int Sum[Maxnum];  //记录总分
	int B[Maxnum];    //辅助排序学号
	system("cls");
	if (count > 0) {		//信息数目大于0，说明存在信息
		printf("\n\n\t\t\t		这是全部的学生信息,一共%d位\n\n", count);
		printf("序号\t学号\t姓名\t性别\t年龄\t家庭住址\t语文\t数学\t英语\t物理\t化学\t生物\t总分\n");
		for (int i = 0;i < count;i++) {		//将序号，和信息全部显示
			B[i] = info[i].Idnumber;
			Sum[i] = info[i].Score[0] + info[i].Score[1] + info[i].Score[2] + info[i].Score[3] + info[i].Score[4] + info[i].Score[5];
			printf("%d\t%d\t%s\t%s\t%d\t%-16s", info[i].Num, info[i].Idnumber, info[i].Name, info[i].Sex, info[i].Age, info[i].Hometown);
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5], Sum[i]);
		}
		while (1) {
			printf("\n\t\t\t		可以输入\n");
			printf("\t\t\t		1-按总分排序\n");
			printf("\t\t\t		2-按学号排序来再次显示\n");
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
				for (int i = 0;i < count;i++) {
					for (int j = 0;j < count;j++) {
						int sum = info[j].Score[0] + info[j].Score[1] + info[j].Score[2] + info[j].Score[3] + info[j].Score[4] + info[j].Score[5];
						if (Sum[i] == sum) {	//将排好序的总分与原来的总分匹配，并显示
							printf("%d\t%d\t%s\t%s\t%d\t%-16s", i + 1, info[j].Idnumber, info[j].Name, info[j].Sex, info[j].Age, info[j].Hometown);
							printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[j].Score[0], info[j].Score[1], info[j].Score[2], info[j].Score[3], info[j].Score[4], info[j].Score[5], sum);
						}
					}
				}
				system("pause");
				printf("\t\t\t		即将返回主菜单\n");
				system("pause");
				InputChoice();
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
					for (int j = 0;j < count;j++) {
						if (B[i] == info[j].Idnumber) {	//将排好序的学号与原来的学号匹配，并显示
							printf("%d\t%d\t%s\t%s\t%d\t%-16s", i + 1, info[j].Idnumber, info[j].Name, info[j].Sex, info[j].Age, info[j].Hometown);
							printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[j].Score[0], info[j].Score[1], info[j].Score[2], info[j].Score[3], info[j].Score[4], info[j].Score[5], Sum[j]);
						}
					}
				}
				system("pause");
				printf("\t\t\t		即将返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else if (choice == 3) {
				printf("\t\t\t		正在返回主菜单\n");
				system("pause");
				InputChoice();
			}
			else {
				printf("\t\t\t		请输入1、2或3！\n");
				system("pause");
			}
		}
	}
	else {
		printf("\t\t\t		系统中没有任何信息！\n");
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
	if ((fp1 = fopen("StudentScore.txt", "w")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		exit(0);
	}
	for (int i = 0;i < count;i++) {
		fprintf(fp1, " %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", info[i].Num, info[i].Idnumber, info[i].Score[0], info[i].Score[1], info[i].Score[2], info[i].Score[3], info[i].Score[4], info[i].Score[5]);
	}
	if (fclose(fp1)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
	//学生基本信息文件
	if ((fp2 = fopen("StudentInfo.txt", "w")) == NULL) {
		printf("\t\t\t		无法打开文件！\n");
		exit(0);
	}
	for (int i = 0;i < count;i++) {
		fprintf(fp2, "%d\t%s\t%s\t%s\t%d\n", info[i].Idnumber, info[i].Name, info[i].Sex, info[i].Hometown, info[i].Age);
	}
	if (fclose(fp2)) {
		printf("\t\t\t		无法关闭文件！\n");
		exit(0);
	}
}
//问候模块，用于开始和结束
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