
## 1、扫描周期与时钟节拍
一般小型系统由Background和Foreground构成。Background称为任务区，Foreground称为中断区。对实时性要求很高的操作要由中断区的中断服务程序来完成。位于Background区域的任务响应时间取决于超级循环（Super-Loops）执行一次的时间，也称之为扫描周期ScanCycleTime。扫描周期并不固定，任务执行过程中扫描周期的最大值意味着任务最坏的响应时间。

microLite裸机系统最小的时间单位是时钟节拍（Tick），时钟节拍是特定的周期性中断，这个中断可以看做是系统心跳，时钟节拍由硬件定时器产生，当中断到来时，将调用一次ml_tick_increase()。不同硬件定时器的中断实现不同，下面的中断函数以 STM32 定时器作为示例：
```
void SysTick_Handler(void)
{
    ml_tick_increase();
}
```
在中断函数中调用 ml_tick_increase()对全局变量 ml_tick 进行自加，代码如下：
```
void ml_tick_increase(void)
{
    ml_tick++;
}
```
通过调用 ml_tick_get会返回当前 ml_tick 的值，即可以获取到当前的时钟节拍值。此接口可用于获取系统的最大扫描周期，或者测量某任务运行的时间。接口函数如下：

```
ml_tick_t ml_tick_get(void)
{
    ml_tick_t t = 0;
    t = ml_tick;
    while (t != ml_tick) {
        t = ml_tick;
    }
    return t;
}
```


## 2、软件定时器microLite_timer介绍

软件定时器microLite_timer提供两类定时器机制：
- 第一类是周期触发定时器（MLPeriod），这类定时器会周期性的触发定时器，并且“一旦启动，永不停止”。

- 第二类是单次触发定时器（MLShot），这类定时器在启动后只会触发一次定时器事件，然后定时器自动停止。

## 3、应用场景
周期触发定时器（MLPeriod），适用于对首次触发时间要求不严格的场合。比如，让LED以280ms周期性亮灭。这种情况下我们并不关心LED首次由灭到亮用了多长时间，我们只要求LED在以后的时间以准确的280ms周期性亮灭。

单次触发定时器（MLShot），适用于对首次触发时间要求严格的场合。另外MLshot定时器自动停止后，调用启动函数MLShot.start，亦可实现周期触发。

## 4、API接口
microLite_timer支持的MLPeriod接口主要包括：
- MLPeriod.Init，初始化定时器；
- MLPeriod.run；
- MLPeriod.check，检查定时器是否超时。

microLite_timer支持的MLShot接口主要包括：
- MLShot.start，启动定时器；
- MLShot.stop，停止定时器；
- MLShot.check，检查定时器是否超时。

## 5、注意事项

- MLPeriod.run在一个扫描周期内，应被调用一次且仅一次；
- 不建议将MLPeriod.check的参数设置为不固定值；
- 不建议嵌套使用MLPeriod.check；
- MLPeriod支持定时周期不同的定时器的个数为ML_PERIODTIMER_MAX；
- MLShot触发后，定时器自动停止；
- microLite_timer的定时精度由系统Tick时钟的周期以及扫描周期决定。

