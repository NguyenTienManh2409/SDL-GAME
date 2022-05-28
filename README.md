Họ và Tên: Nguyễn Tiến Mạnh   MSSV: 21020777
BÁO CÁO BÀI TẬP CUỐI KÌ MÔN LẬP TRÌNH NÂNG CAO

I, Hướng dẫn cài đặt
Em sẽ hướng dẫn cài đặt trên VISUAL STUDIO

B1: Download phiên bản VISUAL STUDIO 2022 

B2: Liên kết các thư viện SDL và dự án

    - Download file zip và giải nén
    - Mở file SDL Game.sln
    - Mở properties của project
    - Vào mục VC++ Directories : .
         + Chọn Include Directories : add các đường link
              . $(SolutionDir)SDL2-2.0.22\include
              . $(SolutionDir)SDL2_image-2.0.5\include
              . $(SolutionDir)SDL2_mixer-2.0.4\include 
              . $(SolutionDir)SDL2_ttf-2.0.18\include
         + Chọn Library Directories : add các đường link
              . $(SolutionDir)SDL2_ttf-2.0.18\lib\x64
              . $(SolutionDir)SDL2_image-2.0.5\lib\x64 
              . $(SolutionDir)SDL2_mixer-2.0.4\lib\x64
              . $(SolutionDir)SDL2-2.0.22\lib\x64
         + Vào mục Linker chọn Input điền :
              SDL2.lib
              SDL2main.lib
              SDL2_image.lib
              SDL2_mixer.lib
              SDL2_ttf.lib
              
B3: Dẫn path vào thư mục lib 

- Mở Edit enviroment variables... 
- Sau đó vào path -> new -> browser đến các file lib/x64 trong từng thư viện

B4: Thoát ra vào lại và chạy bình thường 

II, Mô tả chung về trò chơi : Game bắn gà
- Người chơi di chuyển con tàu của mình để né đạn đồng thời bắn hạ các kẻ địch 
- Sử dụng các phím W A S D để di chuyển và SPACEBAR để bắn đạn
- Có các phần quà nâng cấp đạn khi tiêu diệt được số lượng địch nhất định
- Khi tiêu diệt đến số lượng địch nhất định thì Boss sẽ xuất hiện

III, Mô tả các chức năng đã cài đặt
- Màn hình menu : Start game để bắt đầu, Tutorial để xem hướng dẫn, Exit để thoát game 
- Hệ thống âm thanh hoàn chỉnh: Nhạc nền, hiệu ứng âm thanh khi click chuột, ...
- Hệ thống đồ họa hiển thị được lập trình với SDL 2.0
- Di chuyển nhân vật bằng các phím 
- Có các kẻ địch di chuyển cũng như có đạn bắn.
- Cuộn background

Link youtube demo: https://youtu.be/f2rQfB0FERw

IV, Các kỹ thuật lập trình được sử dụng trong chương trình
- Cấu trúc dữ liệu: Mảng, Vector.
- Làm việc với con trỏ
- Sử dụng các hằng tránh trường hợp magic number.
- Struct, Class.
- Kĩ thuật tách file và refactor code
- Kĩ thuật lập trình hướng đối tượng 
- Thư viện đồ họa SDL2: SDL2_image-2.0.5, SDL2_mixer-2.0.4, SDL2_ttf-2.0.18, SDL2 2.0.22>
 
V, Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình

a, Điều tâm đắc rút ra được sau khi hoàn thiện chương trình 

- Học được cách vận hành của một game, đặc biệt là các game loop
- Cách sử dụng SDL 2.0 để tạo một chương trình đồ họa có đồ họa và âm thanh
- Củng cố kiến thức sử dụng ngôn ngữ lập trình C++
- Kĩ thuật lập trình hướng đối tượng
- Cách tổ chức các file của project 

b, Hướng phát triển tiếp theo:

- Thêm một người chơi nữa
- Thêm các chức năng pause/resume game
- Xử lí thêm các hướng đạn bắn và thêm các item phụ trợ cũng như đa dạng hơn
- Cải thiện đồ họa, thêm tính năng tùy chỉnh phi thuyền của người chơi
- Một hệ thống tạo độ khó tự chọn
- Thêm chức năng high score 

c, Kết luận:

Sau khi hoàn thành dự án game cuối kì này, em học được rất nhiều kiến thức và kinh nghiệm, từ việc lên ý tưởng cho đến việc cách làm việc, quản lý thời gian. Tuy project còn khá thô sơ nhưng đây là project đầu tiên của em nên đã để lại dấu ấn trong cuộc đời em. Và cuối cùng là việc làm game đã tiếp thêm niềm đam mê lập trình cho bản thân em sau này.
    
 
 


    
              
              
