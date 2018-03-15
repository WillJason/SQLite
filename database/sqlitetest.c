#include <stdio.h>
#include "sqlite3.h"
int select_callback(void * data, int col_count, char ** col_values, char ** col_Name);
int main(int argc, char * argv[])
{
  const char * sSQL1 = "create table users(userid varchar(20) PRIMARY KEY, age int, birthday datetime);";
  char * pErrMsg = 0;
  int result = 0;
  sqlite3 * db = 0;
  int ret = sqlite3_open("./test.db", &db);
  if( ret != SQLITE_OK ) {
    fprintf(stderr, "无法打开数据库：%s", sqlite3_errmsg(db));
    return(1);
  }
  printf("数据库连接成功！\n");
  sqlite3_exec( db, sSQL1, 0, 0, &pErrMsg );
  if( ret != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", pErrMsg);
    sqlite3_free(pErrMsg);
  }
  result = sqlite3_exec( db, "insert into users values('张七',21,'2011-7-24');", 0, 0, &pErrMsg);
  if(result == SQLITE_OK){
    printf("插入数据成功\n");
  }
  result = sqlite3_exec( db, "insert into users values('李六',23,'2012-9-24');", 0, 0, &pErrMsg);
  if(result == SQLITE_OK){
    printf("插入数据成功\n");
  }
  printf("查询数据库内容\n");
  sqlite3_exec( db, "select * from users;", select_callback, 0, &pErrMsg);
  sqlite3_close(db);
  db = 0;
  printf("数据库关闭成功！\n");

  return 0;
}

int select_callback(void * data, int col_count, char ** col_values, char ** col_Name)
{
  int i;
  for( i=0; i < col_count; i++){
    printf( "%s = %s\n", col_Name[i], col_values[i] == 0 ? "NULL" : col_values[i] );
  }

  return 0;
}
