import pandas as pd
from collections import defaultdict

st_df = pd.read_csv('./subway_infor_.csv', sep=',')
st_infor = defaultdict(dict)

for j in range(st_df.shape[0]):
    
    st_name = st_df['STATN_NM'].loc[j]
    if pd.notnull(st_df['SUBWAY_LINE'].loc[j]):
        st_infor[st_name]['호선'] = st_df['SUBWAY_LINE'].loc[j].split(',')
        st_infor[st_name]['주변역'] = st_df['SUBWAY_NEAR'].loc[j].split(',')
        