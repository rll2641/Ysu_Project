import Station_Information as si

# 최단 경로에서 환승찾기
def transfer(route):
    
    # 시작 라인 찾기
    def select_start_line(route, idx):
        start_line = si.st_infor[route[idx]]['호선']
        
        if len(start_line) > 1:
            start_line = "".join([i for i in start_line if i in si.st_infor[route[idx + 1]]['호선']])
        else:
            start_line = "".join(start_line)
        
        return start_line
    
    start_line = select_start_line(route, 0)
    transfer_line = []
    
    # 환승 발생 여부
    for idx, station in enumerate(route):
        if start_line not in si.st_infor[station]['호선']:
            save_line = start_line
            start_line = select_start_line(route, idx-1)
            transfer_line.append([route[idx-1], save_line, start_line])

    # tkinter
    save_tr = []
    if len(transfer_line) > 0:
        for tr in transfer_line:
            save_tr.append(tr.pop(0) + ' '  + '->'.join(tr))
        return save_tr