import type { Point2D, Segment2D } from '../types'

const API_BASE = import.meta.env.VITE_API_BASE

export type Intersection = {
  point: Point2D
  segments: { start: Point2D; end: Point2D }[]
}

export async function fetchLineSegmentIntersection(
  segments: Segment2D[]
): Promise<Intersection[]> {
  const res = await fetch(`${API_BASE}/api/line-segment-intersection`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ segments }),
  })
  return res.json()
}