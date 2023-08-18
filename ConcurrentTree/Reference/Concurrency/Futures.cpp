/*
future를 사용하면 스레드의 실행 결과를 쉽게 받아올 수 있을 뿐만 아니라
예외를 다른 스레드로 전달해서 원하는 방식으로 처리할 수 있습니다.
물론 예외가 발생한 스레드에서 벗어나지 않도록 항상 같은 스레드 안에서 예외를 처리하는 것이 바람직합니다.
 스레드의 실행 결과를 promise에 담으면 future로 그 값을 가지고 있습니다.
 channel에 비유하면 promise는 입력 포트이고, future는 출력 포트인 셈입니다.
 같은 스레드나 다른 스레드에서 실행하는 함수가 계산해서 리턴하는 값을 promise에 담으면
 나중에 그 값을 future에서 가져갈 수 있습니다.
 이 메커니즘은 결과에 대한 스레드 통신 채널로 볼 수 있습니다.
 */
std::future<T> myFuture{};
T result{myFuture.get()}; // get을 호출해서 가져온 결과를 result변수에 저장
// get계산이 끝날 때까지 멈추고 기다리며(블록됨), future하나에 get()하나 사용가능.

if (myFuture.wait_for(0))
{ // value is available
    T result{myFuture.get()};
}
else
{
}