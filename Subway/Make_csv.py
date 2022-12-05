import pandas as pd
from bs4 import BeautifulSoup
import requests

key = '5378554e65616c6c313038555a51524f'
url = 'http://swopenapi.seoul.go.kr/api/subway/' + key + '/xml/realtimeStationArrival/0/20/'
pd.set_option('mode.chained_assignment', None)

st_df = pd.read_csv('./실시간도착_역정보_221028.csv', sep=",")
st_df['SUBWAY_LINE'] = None
st_df['SUBWAY_NEAR'] = None
st_infor = list()

st_line_name = {
    '1001': '1호선',
    '1002': '2호선',
    '1003': '3호선',
    '1004': '4호선',
    '1005': '5호선',
    '1006': '6호선',
    '1007': '7호선',
    '1008': '8호선',
    '1009': '9호선',
    '1092': '우이신설경전철',
    '1067': '경춘선',
    '1063': '경의중앙',
    '1075': '수인분당선',
    '1077': '신분당',
    '1065': '공항철도'
}

if __name__ == "__main__":
    
    for j in range(st_df.shape[0]):
        
        st_name = st_df['STATN_NM'].loc[j]
        if st_name in st_infor:
            continue
        
        st_result = requests.get(url + st_name, verify=False)
        st_soup = BeautifulSoup(st_result.text, "lxml-xml")
        
        # api를 통해 몇 호선인지 찾기
        st_line_list = pd.Series(st_soup.findAll('subwayId')).unique()
        st_line_list = [line.text for line in st_line_list]
        # ['1001', '1002'] '1001' -> '1호선' 변환
        st_line_list = [st_line_name.get(trans) for trans in st_line_list if trans in st_line_name]
        st_line_list.sort()
        st_df['SUBWAY_LINE'].loc[j] = ','.join(st_line_list)

        # api를 통해 인접한 역 찾기
        st_left_list = pd.Series(st_soup.findAll('statnFid')).unique()
        st_left_list = [st.text for st in st_left_list]
        
        st_right_list = pd.Series(st_soup.findAll('statnTid')).unique()
        st_right_list = [st.text for st in st_right_list]
        
        st_near_list = pd.Series(st_left_list + st_right_list).unique()
        st_near_list = [int(st) for st in st_near_list]
        # [1001000100, 1001000102] -> '소요산', '보산' 변환
        idx = st_df.index[st_df['STATN_ID'].isin(st_near_list)].tolist()
        # 중복 및 자기 자신 삭제
        st_lst = [st_df.loc[i].STATN_NM for i in idx if st_df.loc[i].STATN_NM != st_name]
        st_lst = list(pd.Series(st_lst).unique())
        st_df['SUBWAY_NEAR'].loc[j] = ','.join(st_lst)
        
        st_infor.append(st_name)

    # csv파일 저장
    st_df.to_csv('subway_infor_.csv', index=False)