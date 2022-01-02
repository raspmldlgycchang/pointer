#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

#define MAX_LEN 240
typedef unsigned int HANDLE;
struct HandleData {
	HANDLE h;
	char* mp_string;
};
typedef struct HandleData HandleData;
void error_handling(const char* msg);
class Tipsware {
private:
	unsigned int m_len, m_max_len;
public:
	void SetString(const char* ap_string);
	void Destroy();
};
class HandleUsers {
private:
	HandleData** mp_users;
	unsigned int m_max_count, m_max_user_cnt;
	unsigned int m_gen_value;
public:
	HandleUsers(unsigned int a_max_user_cnt = 3, unsigned int a_max_count = 2) {
		m_max_count = a_max_count-1;
		m_max_user_cnt = a_max_user_cnt-1;
		mp_users = new HandleData * [m_max_user_cnt];
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			*(mp_users + j) = new HandleData[m_max_count];

		}
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			memset(*(mp_users + j), 0, sizeof(HandleData)*m_max_count);
		}
		m_gen_value = 1;
	}
	~HandleUsers() {
		Destroy();
	}
	void Destroy() {
		HandleData* p_handle = mp_users[0];
		//HandleData*p_handle = &mp_users[0][0];
		for (unsigned int j = 0; j < m_max_count; j++) {
			p_handle = &mp_users[j][0];
			unsigned int i;
			for (i = 0; i < m_max_count; i++) {
				if (p_handle->h) {//p_handle->h�� 0�� �ƴ϶�� ���� �� �ּҿ� ���ڿ��� SetString�Լ����� ����ǰ� �� ����ü ������ �ڵ鰪 ��Ұ� ��ȯ�Ǿ��ٴ� �ǹ��̴�
					delete[] p_handle->mp_string;
				}
			}
			delete[] mp_users[j];
		}
		delete mp_users;
	}
	HANDLE SetString(const char* ap_string);
	void ShowString(HANDLE h_str);
};
HANDLE HandleUsers::SetString(const char* ap_string)
{
	int len = strlen(ap_string) + 1;
	HandleData* p_handle = &mp_users[0][0];
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
		p_handle = &mp_users[j][0];
		unsigned int i;
		for (i = 0; i < m_max_count; i++) {
			if ((p_handle->h) == 0) {
				break;
			}
			else {
				p_handle++;
			}
		}
		if (i < m_max_count) {
			p_handle->mp_string = new char[len];
			memcpy(p_handle->mp_string, ap_string, len);
			p_handle->h = m_gen_value++;
			return p_handle->h;
		}
		else if (j < m_max_user_cnt) {
			p_handle = &mp_users[j++][0];
			for (i = 0; i < m_max_count; i++) {
				if ((p_handle->h) == 0) {
					break;
				}
				else {
					p_handle++;
				}
			}
			if (i < m_max_count) {
				p_handle->mp_string = new char[len];
				memcpy(p_handle->mp_string, ap_string, len);
				p_handle->h = m_gen_value++;
				return p_handle->h;
			}
			else {
				printf("���� ������ ����ڰ� ���ҽ��ϴ�\n");
				p_handle = &mp_users[j++][0];
				for (i = 0; i < m_max_count; i++) {
					if ((p_handle->h) == 0) {
						break;
					}
					else {
						p_handle++;
					}
				}
				if (i < m_max_count) {
					p_handle->mp_string = new char[len];
					memcpy(p_handle->mp_string, ap_string, len);
					p_handle->h = m_gen_value++;
					return p_handle->h;
				}
			}
		}
		else {
			printf("�����ֽ� ����� ���� �Ѿ����ϴ�\n");
			return 0xFFFFFFFF;
		}
	}

}
void  HandleUsers::ShowString(HANDLE h_str)
{
	HandleData* p_handle = mp_users[0];
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
		p_handle = &mp_users[j][0];
		unsigned int i;
		for (i = 0; i < m_max_count; i++) {
			if (h_str == p_handle->h)
				break;
			else
				continue;
		}
		printf("%s: ã������ �ڵ鰪�� ���� ���ڿ��Դϴ�\n", p_handle->mp_string);
	}
	fputs((const char*)"ã������ �ڵ鰪�� �����ϴ�", stdout);
	rewind(stdin);
}
void error_handling(const char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(0);
}
int GetMyString(char buf[], int limit)//limit:�迭ũ��
{
	unsigned int i;
	//limit-1���� �־����
	for (i = 0; i < limit - 1; i++) {
		buf[i] = getchar();
		if (buf[i] == '\n') {
			buf[i] = 0;
			return 1;
		}
	}
	buf[i] = 0;//i==limit
	fputs((const char*)"�����ֽ� ���ڿ����̸� �Ѿ����ϴ�", stdout);
	return 0;
}

int main(void)
{
	HandleUsers str_users_lists;
	HANDLE h_user1_str1 = str_users_lists.SetString("�ȳ��ϼ���");
	printf("%u:h_user1_str1\n", h_user1_str1);//1
	HANDLE h_user1_str2 = str_users_lists.SetString("���� ���������Դϴ�");
	printf("%u:h_user1_str2\n", h_user1_str2);//2
	HANDLE h_user2_str1 = str_users_lists.SetString("���� ����� ��ϴ�");
	printf("%u:h_user2_str1\n", h_user2_str1);//3
	HANDLE h_user2_str2 = str_users_lists.SetString("���� ���������� ���մϴ�");
	printf("%u:h_user2_str1\n", h_user2_str1);//3
	HANDLE h_error_user = str_users_lists.SetString("�� ���忭�� ������ �����ϴ�");

	str_users_lists.ShowString(h_user1_str1);
	str_users_lists.ShowString(h_user1_str2);
	str_users_lists.ShowString(h_user2_str1);
	str_users_lists.ShowString(h_user2_str2);
	str_users_lists.ShowString(h_error_user);
	return 0;
}