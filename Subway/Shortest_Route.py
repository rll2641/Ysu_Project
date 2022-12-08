from collections import deque
import Station_Information as si
from Subway_csv import st_line_name as sl

'''
환승이 불필요한 경우
- 출발역의 라인과 도착역의 라인이 동일한 경우.

-> 같은 호선에서만 이동 (dfs)

환승이 필요한 경우
- 출발역의 라인과 도착역의 라인이 다른 경우.
- 환승 1번, 2번, 그 이상의 경우로 구분.

조건1. 환승 1번인 경우
-> 출발 역을 기준으로 투 포인터 적용
-> 포인터를 움직여 환승 역의 라인과 도착 역의 라인이 겹치는 역을 탐색
-> 탐색한 역에서 dfs진행

조건2. 환승 2번인 경우
-> 도착 라인의 모든 환승라인을 리스트에 저장
-> 출발 역을 기준으로 투 포인터 적용
-> 환승 역의 라인과 도착라인의 모든 환승라인이 매칭되는지 확인
-> 매칭 될 시, 환승역에서 도착라인의 환승역까지 dfs, 그 환승역에서 도착역까지 dfs
-> 투 포인터를 전부 움직여 매칭 후, 그 중 가장 길이가 짧은 경로를 선택

조건3. 환승 3번 이상인 경우
-> 환승 3번이상인 경우는 존재하긴 하나, api에서 제공하는 라인들의 경우
   독립된 라인이 없기에 경우의 수가 극소수이다. 
-> 따라서 조건 1,2번의 경우가 없을 경우, bfs를 통해 가장 짧은 경로를 택한다.
'''

# 환승이 불필요한 경우(dfs)
def shortest_route_dfs(start, end, st_line):
    st_deque = deque([[start]])
    visited = [start]
    
    while st_deque:
        st_route = st_deque.popleft()
        st_node = st_route[-1]
        
        if st_node == end:
            return st_route
        
        for st in si.st_infor.get(st_node).get('주변역'):
            # 같은 라인에서 역 이동(깊이 탐색)
            if st_line not in si.st_infor.get(st).get('호선'):
                continue
            if st not in visited:
                visited.append(st)
                route = list(st_route)
                route.append(st)
                st_deque.append(route)

# 환승이 필요한 경우(투 포인터 + dfs), 조건1
def shortest_route_dfs_1(start, end):
    st_line_name = {i:j for j, i in sl.items()}
    line_list = si.st_infor.get(start).get('호선')
    line_list = [int(st_line_name.get(line)) for line in line_list]
    
    # 호선별 전체역 리스트
    for line in line_list:
        st_list = list(si.st_df.loc[si.st_df['SUBWAY_ID'] == line].STATN_NM)
        
        # 투 포인터
        left = st_list.index(start) - 1
        right = st_list.index(start) + 1
        left_visited, right_visited = [start], [start]
        left_short_route = right_short_route = [0 for _ in range(50)]
        
        while left != -1 or right != len(st_list) - 1:
            
            for line in si.st_infor.get(st_list[left]).get('호선'):
                if line in si.st_infor.get(end).get('호선'):
                    route = shortest_route_dfs(st_list[left], end, line)
                    route = left_visited + route
                    left_short_route = min(left_short_route, route, key=len)

            for line in si.st_infor.get(st_list[right]).get('호선'):
                if line in si.st_infor.get(end).get('호선'):
                    route = shortest_route_dfs(st_list[right], end, line)
                    route = right_visited + route
                    right_short_route = min(right_short_route, route, key=len)
                
            left_visited.append(st_list[left])
            right_visited.append(st_list[right])
            
            left -= 1
            right += 1
            
            if left < 0:
                left = -1
            if right > len(st_list) - 1:
                right = len(st_list) - 1
        
    shortest_route = min(left_short_route, right_short_route, key=len)
    return shortest_route

# 환승이 필요한 경우(투 포인터 + dfs), 조건2
def shortest_route_dfs_2(start, end, ed_line):
    st_line_name = {i:j for j, i in sl.items()}
    start_line_list = [int(st_line_name.get(line)) for line in si.st_infor.get(start).get('호선')]
    
    # 호선별 전체역 리스트
    for st_line in start_line_list:
        start_line = list(si.st_df.loc[si.st_df['SUBWAY_ID'] == st_line].STATN_NM)
        
        # 투 포인터
        left = start_line.index(start) - 1
        right = start_line.index(start) + 1
        left_visted, right_visited = [start], [start]
        left_line_visited, right_line_visited = [], []
        left_short_route = right_short_route = [0 for _ in range(50)]
        
        while left != -1 or right != len(start_line) - 1:
            
            try:
                # 왼쪽 포인터
                for line in si.st_infor.get(start_line[left]).get('호선'):
                    if line not in si.st_infor.get(end).get('호선') and line not in si.st_infor.get(start).get('호선'):
                        st_list = si.st_df.loc[si.st_df['SUBWAY_LINE'].str.contains(line, na=False)]
                        st_list = list(st_list.loc[st_list['SUBWAY_LINE'].str.contains(ed_line, na=False)].STATN_NM)
                        
                        if line not in left_line_visited:
                            left_line_visited.append(line)
                            for stnm in st_list:
                                tr_1 = shortest_route_dfs(start_line[left], stnm, line)
                                tr_1.pop()
                                tr_2 = shortest_route_dfs(stnm, end, ed_line)
                                left_route = left_visted + tr_1 + tr_2
                                left_short_route = min(left_short_route, left_route, key=len)
                
                # 오른쪽 포인터
                for line in si.st_infor.get(start_line[right]).get('호선'):
                    if line not in si.st_infor.get(end).get('호선') and line not in si.st_infor.get(start).get('호선'):
                        st_list = si.st_df.loc[si.st_df['SUBWAY_LINE'].str.contains(line, na=False)]
                        st_list = list(st_list.loc[st_list['SUBWAY_LINE'].str.contains(ed_line, na=False)].STATN_NM)
                        
                        if line not in right_line_visited:
                            right_line_visited.append(line)
                            for stnm in st_list:
                                tr_1 = shortest_route_dfs(start_line[right], stnm, line)
                                tr_1.pop()
                                tr_2 = shortest_route_dfs(stnm, end, ed_line)
                                right_route = right_visited + tr_1 + tr_2 
                                right_short_route = min(right_short_route, right_route, key=len)
            except AttributeError:
                return [0 for _ in range(50)]
            except TypeError:
                return [0 for _ in range(50)]

            left_visted.append(start_line[left])
            right_visited.append(start_line[right])
            
            left -= 1
            right += 1
            
            if left < 0:
                left = -1
            if right > len(start_line) - 1:
                right = len(start_line) - 1
    
    shortest_route = min(left_short_route, right_short_route, key=len)
    return shortest_route

# 조건1,2번이 없을 경우(bfs), 조건3
def shortest_route_bfs_3(start, end):
    st_deque = deque([[start]])
    visited = [start]
    
    while st_deque:
        st_deque = deque([dele for dele in st_deque if len(dele) < 30])
        
        st_route = st_deque.popleft()
        st_node = st_route[-1]
        
        if st_node == end:
            return st_route
        try:
            for st in si.st_infor.get(st_node).get('주변역'):
                if st not in visited:
                    visited.append(st)
                    route = list(st_route)
                    route.append(st)
                    st_deque.append(route)
        except:
            pass