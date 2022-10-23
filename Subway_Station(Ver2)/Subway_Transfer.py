from collections import deque
import Subway_Information as si

# 환승
def transfer(route):
    transfer_line = deque([])
    
    # 출발점의 호선을 기억하는 함수
    def select_start_line(route, idx):
        start_line = si.station_information[route[idx]]['호선']
        
        # 출발점의 호선이 2개 이상일 경우
        if len(start_line) > 1:
            start_line = "".join([i for i in start_line if i in si.station_information[route[idx + 1]]['호선']])
        else:
            start_line = "".join(start_line)
        
        return start_line
    
    start_line = select_start_line(route, 0)
    
    # 환승 발생 여부
    transfer_bool = False
    for idx, station in enumerate(route):
        if start_line not in si.station_information[station]['호선']:
            save_line = start_line
            start_line = select_start_line(route, idx-1)
            transfer_line.append([route[idx-1], save_line, start_line])
            transfer_bool = True
    
    # tkinter 상호작용을 위해 
    if transfer_bool:
        tr_str = []
        for i in range(len(transfer_line)):
            save = transfer_line.popleft()
            tr_str.append(save.pop(0) + '역 ' + '->'.join(save))
    
    return tr_str

def transfer_dict(route):
    
    if len(route) < 2:
        return 0
    
    # 출발점의 호선을 기억하는 함수
    def select_start_line(route, idx):
        start_line = si.station_information[route[idx]]['호선']
        
        # 출발점의 호선이 2개 이상일 경우
        if len(start_line) > 1:
            start_line = "".join([i for i in start_line if i in si.station_information[route[idx + 1]]['호선']])
        else:
            start_line = "".join(start_line)
        
        return start_line
    
    start_line = select_start_line(route, 0)
    
    # 환승 발생
    transfer_cnt = 0
    for idx, station in enumerate(route):
        if start_line not in si.station_information[station]['호선']:
            start_line = select_start_line(route, idx-1)
            transfer_cnt += 1
    
    return transfer_cnt