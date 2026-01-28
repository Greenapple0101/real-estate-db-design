# Real Estate DB Design (DB Project2)

MySQL 데이터베이스(부동산 매물/거래/중개인)를 설계하고, **MySQL C API**를 이용해 콘솔 프로그램에서 다양한 조회/분석/기록 기능을 수행하는 프로젝트입니다.

## 프로젝트 구성

- `\[project2]20221197.cpp`: 콘솔 프로그램 소스 (MySQL 접속 후 메뉴 기반 쿼리 실행)
- `CRUD.txt`: DB 생성/테이블 생성/샘플 데이터 삽입 SQL 스크립트
- `20221197.erwin`: ERwin 모델 파일
- `20221197.png`: ERD 이미지(또는 다이어그램)

## 실행 환경

- **MySQL Server** (로컬 실행)
- **MySQL C API / Connector/C** (헤더 `mysql.h`, 라이브러리 `libmysql.lib` 또는 `libmysqlclient`)
- Windows 기준으로는 Visual Studio에서 빌드(현재 코드에 `#pragma comment(lib, "libmysql.lib")` 포함)

## DB 세팅

1) MySQL 서버를 실행합니다.

2) `CRUD.txt`를 MySQL에서 실행해 DB/테이블/샘플 데이터를 구성합니다.

- DB 이름: `project`
- 실행 예시(MySQL CLI):

```sql
SOURCE CRUD.txt;
```

> `CRUD.txt`는 `DROP DATABASE IF EXISTS project;`를 포함합니다. 기존 `project` DB가 있다면 삭제될 수 있으니 주의하세요.

## 프로그램 설정(중요)

`[project2]20221197.cpp` 상단의 DB 접속 정보를 본인 환경에 맞게 수정해야 합니다.

- `host`, `user`, `pw`, `db` 값 확인/수정
- 기본값은 아래처럼 되어 있습니다:
  - host: `127.0.0.1`
  - user: `root`
  - pw: `asdf`
  - db: `project`

## 빌드/실행

### Windows (Visual Studio 권장)

1) MySQL Connector/C(또는 MySQL Server 설치 시 제공되는 개발 파일)를 설치합니다.
2) 프로젝트에 include/lib 경로를 연결합니다.
   - include: `...\include` (예: `mysql.h` 위치)
   - lib: `...\lib` (예: `libmysql.lib` 위치)
   - runtime dll: 실행 파일과 같은 폴더에 `libmysql.dll` 필요할 수 있음
3) 빌드 후 실행하면 콘솔에 메뉴가 출력됩니다.

### (참고) GCC 계열

환경에 따라 `libmysqlclient` 링크로 빌드할 수 있습니다(설치/경로는 환경별 상이).

## 기능(메뉴)

프로그램 실행 후 아래 **쿼리 타입**을 선택해 결과를 확인합니다.

### TYPE 1: 특정 구(Mapo) 매물 주소 조회

- **TYPE 1**: `Mapo` 구의 매물 주소 조회
- **TYPE 1-1**: `Mapo` 구 매물 중 가격 범위(1,000,000,000 ~ 1,500,000,000) 조건 추가

### TYPE 2: 학군(8th) 기준 매물 주소 조회

- **TYPE 2**: `8th` 학군의 매물 주소 조회
- **TYPE 2-1**: 침실 \(>=4\), 욕실 \(>=2\) 조건 추가

### TYPE 3: 연도별 중개인 판매 실적 분석

- **TYPE 3**: 2022년 총 판매액 기준 1등 중개인
- **TYPE 3-1**: 2023년 총 판매액 기준 상위 k명(사용자 입력 k)
- **TYPE 3-2**: 2021년 총 판매액 기준 하위 10% (윈도우 함수 `PERCENT_RANK()` 사용)

### TYPE 4: 연도별 평균 판매가/평균 판매까지 소요일 분석

- **TYPE 4**: 2022년 판매 건에 대해
  - 중개인별 평균 판매가
  - 중개인별 평균 판매까지 소요일(판매일 - 등록일)
- **TYPE 4-1**: 2023년 중개인별 최대 판매가
- **TYPE 4-2**: 중개인별 최장 판매까지 소요일

### TYPE 5: 유형별 최고가 매물의 사진(설명) 조회

- studio / one-bedroom / multi-bedroom / detached house 유형별 최고가 매물의 사진 설명(`Photo.description`) 출력
  - 현재 샘플 데이터는 이미지 BLOB 대신 `NULL`과 설명 텍스트를 사용합니다.

### TYPE 6: 매물 판매 기록(available → sold)

- 판매 가능한 매물(`Property.status = 'available'`)을 판매 처리하고 `Sale`에 거래를 기록합니다.
- 입력: property_id, sale_price, buyer_id, agent_id 등

### TYPE 7: 새로운 중개인(Agent) 추가

- 입력: agent_name, agent_contact

## 주의사항 / 한계

- **보안**: 코드에 DB 계정/비밀번호가 하드코딩되어 있습니다. 제출/공유 전 본인 환경 값으로 수정하고, 가능하면 별도 설정 파일/환경변수로 분리하세요.
- **SQL Injection**: 현재는 `sprintf`로 쿼리를 구성합니다. 입력값을 그대로 붙이면 SQL 주입 위험이 있으니, 실사용 시에는 `mysql_real_escape_string` 또는 prepared statement 사용이 권장됩니다.
- **윈도우 함수**: 일부 쿼리는 `PERCENT_RANK()` 등 윈도우 함수를 사용하므로 MySQL 버전에 따라 동작이 달라질 수 있습니다(MySQL 8.0+ 권장).

## 참고 자료

- `CRUD.txt`: 테이블/샘플데이터/컬럼 추가(list_date, type, status 등) 포함

