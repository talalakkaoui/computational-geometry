import type { Point2D } from '../types'

const API_BASE = 'http://localhost:8080'

export async function fetchDistance(a: Point2D, b: Point2D): Promise<number> {
  const res = await fetch(`${API_BASE}/api/distance`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ points: [a, b] }),
  })
  const data: { distance: number } = await res.json()
  return data.distance
}
