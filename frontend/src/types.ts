export type Point2D = { x: number; y: number }

export type Segment2D = { start: Point2D; end: Point2D }

export type Polygon2D = { vertices: Point2D[]; isClosed: boolean }

export type Theme = {
  bg: string
  text: string
  border: string
  axis: string
  tick: string
  tickText: string
  sidebar: string
  sidebarActive: string
}
