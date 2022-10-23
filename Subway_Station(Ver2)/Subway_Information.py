station_information = { 
    '용산': {
        '호선': ['1호선', '경의중앙선'],
        '주변역': ['이촌'],
        '거리': {'이촌': 1.9}
        },
    '이촌': {
        '호선': ['4호선', '경의중앙선'],
        '주변역': ['서빙고', '동작', '용산'],
        '거리': {'용산': 1.9, '서빙고': 1.7, '동작': 2.7}
        },
    '서빙고': {
        '호선': ['경의중앙선'],
        '주변역': ['이촌', '한남'],
        '거리': {'이촌': 1.7, '한남': 1.9}
        },
    '한남': {
        '호선': ['경의중앙선'],
        '주변역': ['서빙고', '옥수'],
        '거리': {'서빙고': 1.9 , '옥수': 1.6}
        },
    '옥수': {
        '호선': ['3호선', '경의중앙선'],
        '주변역': ['한남', '압구정'],
        '거리': {'한남': 1.6, '압구정': 2.1}
        },
    '흑석': {
        '호선': ['9호선'],
        '주변역':['동작'],
        '거리': {'동작': 1.4}
        },
    '동작': {
        '호선': ['4호선', '9호선'],
        '주변역': ['흑석', '구반포', '총신대입구', '이촌'],
        '거리': {'흑석': 1.4, '구반포': 1.0, '총신대입구': 1.8, '이촌': 2.7}
        },
    '구반포': {
        '호선': ['9호선'],
        '주변역': ['동작', '신반포'],
        '거리': {'동작': 1.0, '신반포': 1.0}
        },
    '신반포': {
        '호선': ['9호선'],
        '주변역': ['구반포', '고속터미널'],
        '거리': {'구반포': 1.0, '고속터미널': 1.0}
        },
    '고속터미널': {
        '호선': ['3호선', '7호선', '9호선'],
        '주변역': ['신반포', '잠원', '교대', '내방'],
        '거리': {'신반포': 1.0, '잠원': 1.2, '교대': 1.6, '내방': 2.2}
        },
    '압구정': {
        '호선': ['3호선'],
        '주변역': ['옥수', '신사'],
        '거리': {'옥수': 2.1, '신사': 1.5}
        },
    '신사': {
        '호선': ['3호선', '신분당선'],
        '주변역': ['압구정', '잠원'],
        '거리': {'압구정': 1.5, '잠원': 1.0}
        },
    '잠원': {
        '호선': ['3호선'],
        '주변역': ['신사', '고속터미널'],
        '거리': {'신사': 1.0, '고속터미널': 1.2}
        },
    '총신대입구': {
        '호선': ['4호선', '7호선'],
        '주변역': ['동작', '내방', '사당'],
        '거리': {'동작': 1.8, '내방': 1.0, '사당': 1.1}
        },
    '내방': {
        '호선': ['7호선'],
        '주변역': ['총신대입구', '고속터미널'],
        '거리': {'총신대입구': 1.0, '고속터미널': 2.2}
        },
    '사당': {
        '호선': ['2호선', '4호선'],
        '주변역': ['총신대입구', '방배'],
        '거리': {'총신대입구': 1.1, '방배': 1.6}
        },
    '방배': {
        '호선': ['2호선'],
        '주변역': ['사당', '서초'],
        '거리': {'사당': 1.6, '서초': 1.7}
        },
    '서초': {
        '호선': ['2호선'],
        '주변역': ['방배', '교대'],
        '거리': {'방배': 1.7, '교대': 1.0}
        },
    '교대': {
        '호선': ['2호선', '3호선'],
        '주변역': ['서초', '고속터미널'],
        '거리': {'서초': 1.0, '고속터미널': 1.6}
        }
}