from tkinter import *
import tkinter as tk
import Subway_main as sm
import Subway_transfer as st

# 기본 상태 조정
Subway = Tk()
Subway.title('서울 지하철 최단경로')
Subway.geometry("905x900")
Subway.resizable(True, True)

# 이미지 삽입
subway_image = tk.PhotoImage(file='subway.png')
image_label = tk.Label(Subway, image=subway_image).pack(side='bottom')

# 출발역 및 도착역 텍스트
start_text = tk.Label(Subway, text='출발역', font=('맑은 고딕',20)).place(x=300, y=20)
end_text = tk.Label(Subway, text='도착역', font=('맑은 고딕',20)).place(x=300, y=100)

# 출발역 입력 및 버튼
start_station_input = tk.Entry(Subway, width=10, font=('맑은 고딕',15))
def receive_start():
    return start_station_input.get()
start_station_input.pack(side='top', pady=15, ipady=10)
start_button = tk.Button(Subway, text='확인')
start_button.config(width=12, height=3, command=receive_start)
start_button.place(x=530, y=15)

# 도착역 입력 및 버튼
end_station_input = tk.Entry(Subway, width=10 ,font=('맑은 고딕',15))
def receive_end():
    return end_station_input.get()
end_station_input.pack(side='top', pady=15, ipady=10)
end_button = tk.Button(Subway, text='확인')
end_button.config(width=12, height=3)
end_button.place(x=530, y=100)

# 최단 경로 출력을 위한 새 창
def new_window():
    Subway_route = Toplevel(Subway)
    Subway_route.title('최단 경로')
    Subway_route.geometry("700x700")
    Subway_route.resizable(True, True)
    
    result = sm.transfer(start_station_input.get(), end_station_input.get())
    route = tk.Label(Subway_route, text='경로 : ' + '->'.join(result),  font=('맑은 고딕',20), wraplength=550).place(x=80, y=20)
    
    check_transfer = st.transfer(result)
    tranfer = tk.Label(Subway_route, text='환승 정보 : ' + '\n'.join(check_transfer), font=('맑은 고딕',20)).place(x=80, y=300)
    
# 최단 경로 시작 버튼
shortest_route_botton = Button(Subway, text='시작')
shortest_route_botton.config(width=12, height=3)
shortest_route_botton.config(command=new_window)
shortest_route_botton.place(x=700, y=60)

Subway.mainloop()