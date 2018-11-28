type status = 
  | Init
  | Started

type action = 
  | Start
  | IncrementScore
  | ChangeActiveMole(int)
  | Reset
  | AddIntervalId(option(Js.Global.intervalId))



type state = {
  score: int,
  status: status,
  activeMole: int,
  intervalId: option(Js.Global.intervalId)
}

let initialState : state = {
    score: 0,
    status: Init,
    activeMole: -1,
    intervalId: None,
}

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) => 
    switch (action) {
    | Start => ReasonReact.UpdateWithSideEffects(
      {
        ...state,
        status: Started
      },
      (self) => {
        let intervalId = Js.Global.setInterval(() => {
          let randomInt = Js.Math.random_int(0, 9);
          self.send(ChangeActiveMole(randomInt))
        }, 1000);
        self.send(AddIntervalId(Some(intervalId)))
      }
    )
    | IncrementScore => ReasonReact.Update({...state, score: state.score + 1})
    | ChangeActiveMole(activeMole) => ReasonReact.Update({...state, activeMole})
    | Reset => ReasonReact.Update(initialState)
    | AddIntervalId(intervalId) => ReasonReact.Update({...state, intervalId})
    },
  render: self =>
    <div className="app">
      <div className="game">
        {
          switch (self.state.status) {
          | Init => <Button
              onClick={_click => self.send(Start)}
              text="Start Game!"
            />
          | Started => 
            <>
            <Score score={self.state.score} />
            <Board
              activeMole={self.state.activeMole}
              onHit={() => self.send(IncrementScore)}
            />
            <Button
              onClick={_click => self.send(Reset)}
              text="Reset"
            />
          </>
          }
        }      
      </div>
    </div>,
};