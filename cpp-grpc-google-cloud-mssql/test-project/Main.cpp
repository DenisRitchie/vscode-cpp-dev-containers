#include <iostream>
#include <sstream>

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sqlucode.h>

static void CheckError(SQLRETURN ReturnCode, const char *ErrorMessage, SQLHANDLE SQLHandle, SQLSMALLINT HandleType)
{
    if (ReturnCode != SQL_SUCCESS && ReturnCode != SQL_SUCCESS_WITH_INFO)
    {
        std::ostringstream FailMessageError;
        SQLSMALLINT StateRegistrationNumber = 0;
        SQLCHAR SqlState[7];
        SQLINTEGER NativeErrorCode;
        SQLCHAR DiagnosticMessage[SQL_MAX_MESSAGE_LENGTH];
        SQLSMALLINT CharactersWrittenInDiagnosticMessage;

        fprintf(stderr, "\nThe driver reported the following error %s\n", ErrorMessage);

        do
        {
            ReturnCode = SQLGetDiagRecA(HandleType, SQLHandle, ++StateRegistrationNumber,
                                        SqlState, &NativeErrorCode, DiagnosticMessage, SQL_MAX_MESSAGE_LENGTH,
                                        &CharactersWrittenInDiagnosticMessage);

            if (SQL_SUCCEEDED(ReturnCode))
            {
                FailMessageError
                    << SqlState << ":"
                    << StateRegistrationNumber << ":"
                    << NativeErrorCode << ":"
                    << DiagnosticMessage << std::endl;
            }
        } while (ReturnCode == SQL_SUCCESS);

        std::cerr << FailMessageError.str();
    }
}

void SQLDriverList(SQLHENV EnvironmentHandle)
{
    SQLCHAR Driver[256];
    SQLCHAR Attributes[256];
    SQLSMALLINT DriverMax;
    SQLSMALLINT AttributesMax;
    SQLUSMALLINT Direction{SQL_FETCH_FIRST};
    SQLRETURN ReturnCode;

    // Call SQLDrivers to return ODBC Drivers
    while (SQL_SUCCEEDED(ReturnCode = SQLDrivers(EnvironmentHandle, Direction, Driver, sizeof(Driver), &DriverMax, Attributes, sizeof(Attributes), &AttributesMax)))
    {
        Direction = SQL_FETCH_NEXT;
        printf("\"%s\" - %s\n", Driver, Attributes);
        CheckError(ReturnCode, "SQLDrivers(SQL_HANDLE_ENV)", EnvironmentHandle, SQL_HANDLE_ENV);
    }
}

auto main(int32_t argc, char *argv[]) -> int32_t
{
    SQLCHAR ConnectionString[] =
        "Driver={ODBC Driver 18 for SQL Server};"
        "Server=<SERVER>;"
        "Database=<DATABASE>;Uid=<USER>;Pwd=<PASSWORD>;Encrypt=yes;"
        "TrustServerCertificate=no;Connection Timeout=30;";

    SQLHENV EnvironmentHandle;
    SQLHDBC ConnectionHandle;
    SQLCHAR ConnectionStringOut[1'024];
    SQLSMALLINT ConnectionStringOutMax;
    SQLHSTMT StatementHandle;

    SQLRETURN ReturnCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &EnvironmentHandle);
    CheckError(ReturnCode, "SQLAllocHandle(SQL_HANDLE_ENV)", EnvironmentHandle, SQL_HANDLE_ENV);

    ReturnCode = SQLSetEnvAttr(EnvironmentHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER *)SQL_OV_ODBC3, (SQLINTEGER)NULL);
    CheckError(ReturnCode, "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION)", EnvironmentHandle, SQL_HANDLE_ENV);

    SQLDriverList(EnvironmentHandle);

    ReturnCode = SQLAllocHandle(SQL_HANDLE_DBC, EnvironmentHandle, &ConnectionHandle);
    CheckError(ReturnCode, "SQLAllocHandle(SQL_HANDLE_DBC)", ConnectionHandle, SQL_HANDLE_DBC);

    ReturnCode = SQLSetConnectAttr(ConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, (SQLINTEGER)NULL);
    CheckError(ReturnCode, "SQLSetConnectAttr(SQL_LOGIN_TIMEOUT)", ConnectionHandle, SQL_HANDLE_DBC);

    ReturnCode = SQLDriverConnect(ConnectionHandle, nullptr, ConnectionString, SQL_NTSL, ConnectionStringOut, sizeof(ConnectionStringOut), &ConnectionStringOutMax, SQL_DRIVER_NOPROMPT);
    CheckError(ReturnCode, "SQLDriverConnect(CONNECTION_STRING)", ConnectionHandle, SQL_HANDLE_DBC);

    ReturnCode = SQLAllocHandle(SQL_HANDLE_STMT, ConnectionHandle, &StatementHandle);
    CheckError(ReturnCode, "SQLAllocHandle(SQL_HANDLE_STMT)", StatementHandle, SQL_HANDLE_STMT);

    ReturnCode = SQLExecDirect(StatementHandle, (SQLCHAR *)"SELECT DB_NAME()", SQL_NTSL);
    CheckError(ReturnCode, "SQLExecDirect()", StatementHandle, SQL_HANDLE_STMT);

    SQLCHAR DatabaseName[512];
    ReturnCode = SQLBindCol(StatementHandle, 1, SQL_C_CHAR, &DatabaseName, sizeof(DatabaseName), NULL);
    ReturnCode = SQLFetch(StatementHandle);

    printf("El nombre de la base de datos es: %s\n", DatabaseName);
    return EXIT_SUCCESS;
}
